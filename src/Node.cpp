#include "Node.h"
#include <sstream>
#include <thread>
#include <iostream>

#if defined(__CYGWIN__) // I really want to use std::to_string() as defined in the C++11 standard,
// but no, Cygwin doesn't support it, and I'm building on Windows or Linux depending on where I am.
namespace std {
  template<typename T>
  std::string to_string(const T &n) {
    std::ostringstream stm;
    stm << n;
    return stm.str();
  }
}
#endif

bool Node::_all_finished = false;

void Node::write_output(Frame to_write) {
  _outfile << to_write.src() << ":" << to_write.data();
}

void Node::write_to_socket(Frame to_write) {
  std::string frame_raw = to_write.raw();
  _switch_socket->send(frame_raw.c_str(), frame_raw.length());
}

void Node::send_acknowledgement(Frame to_ack) {
  to_ack.clear();
  write_to_socket(to_ack);
}

Frame Node::read_from_input() {
  std::string input_line, frame_data;
  if (_infile.is_open() and _infile.good()) {
    std::getline(_infile, input_line);
  }

  std::istringstream input_line_stream(input_line);
  uint8_t dst;
  char colon; // Garbage for the separator

  input_line_stream >> dst >> colon >> frame_data;

  return Frame(_num, dst, frame_data);
}

Frame Node::read_from_socket() throw(NodeException) {
  char in_buf[MAX_FRAME_SZ + 1] = {'\0'};

  if (_switch_socket->recv(in_buf, MAX_FRAME_SZ) > 0) {
    std::string frame_contents(in_buf);
    Frame ret_frame(frame_contents);
    return ret_frame;
  } else {
    throw NodeException("Switch disconnected!");
  }
}

bool Node::is_mine(Frame to_check) {
  return to_check.dst() == _num;
}

void Node::set_port(unsigned short port) {
  _switch_socket = new TCPSocket("localhost", port);
}

void Node::handle_frame(Frame frame) {
  if (frame.src() == 0) { // Control frame from the switch; change TCP port to the port specified
    // in the data (in this case, actually made into a string rather than raw bytes!
    istringstream frame_data(frame.data());
    unsigned short port_num;
    frame_data >> port_num;
    set_port(port_num);
  } else if (is_mine(frame)) {
    if (frame.size() == 0) { // Frame is an acknowledgement
      _ack = true;
      // Just let the frame be deleted
    } else { // Normal data frame
      write_output(frame);
      send_acknowledgement(frame);
    }
  }
}

void Node::send_loop() {
  while (not _infile.eof()) {
    Frame current_frame = read_from_input();
    _ack = false;
    while (not _ack) { // Send until acknowledged
      write_to_socket(current_frame);
      std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Sleep for half a second
      // before resending
    }
  }
}

void Node::receive_loop() {
  while (not _all_finished) {
    Frame received_fame = read_from_socket();
    handle_frame(received_fame);
  }
}

Node::Node(uint8_t num, unsigned short switch_tcp_port) :
    _num {num},
    _infile(("node" + std::to_string((unsigned int) num) + ".txt").c_str()),
    _outfile(("Node" + std::to_string((unsigned int) num) + "Output.txt").c_str()) {
  // Connection negotiation
  _switch_socket = new TCPSocket("localhost", switch_tcp_port);
  int attempts = 0;
  while (attempts < 5 and _switch_socket->getForeignPort() == switch_tcp_port) {
    try {
      char buf[128];
      _switch_socket->recv(buf, 127);
      unsigned char new_port = atoi(buf);
      _switch_socket = new TCPSocket("localhost", new_port);
    } catch (SocketException &e) {
      string s(e.what());
      std::cerr << s << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(attempts * 100));
    }
  }

  // Start receive loop in new thread
  std::thread receive_thread(&Node::receive_loop, this);
  receive_thread.detach();

  // Start send loop in new thread
  std::thread send_thread(&Node::send_loop, this);
  send_thread.detach();
}

void Node::set_finished() {
  _all_finished = true;
}
