#include "Node.h"
#include <sstream>

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
    if(_infile.is_open() and _infile.good()) {
        std::getline(_infile,input_line);
    }

    std::istringstream input_line_stream(input_line);
    uint8_t dst;
    char colon; // Garbage for the separator

    input_line_stream >> dst >> colon >> frame_data;

    return Frame(_num, dst, frame_data);
}

Frame Node::read_from_socket() throw(NodeException) {
    char in_buf[MAX_FRAME_SZ+1] = {'\0'};

    if(_switch_socket->recv(in_buf, MAX_FRAME_SZ) > 0) {
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
    if(frame.src() == 0) { // Control frame from the switch

    } else if(is_mine(frame)) {

    }
}