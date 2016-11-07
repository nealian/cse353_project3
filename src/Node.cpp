#include "Node.h"
#include <sstream>
#include <thread>
#include <chrono>

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
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
  while (true) {// eventually give this a flag modifiable by the main() class/function
    Frame rcvd_fame = read_from_socket();
    handle_frame(rcvd_fame);
  }
#pragma clang diagnostic pop
}
