#pragma once

#include "PracticalSocket.h"
#include "Frame.h"
#include <cstdint>
#include <string>
#include <fstream>

class NodeException : public exception {
    string userMessage;
public:
    NodeException(const string &message) throw() : userMessage(message) {};
    ~NodeException() throw() {};
    const char *what() const throw() {return userMessage.c_str();};
};

class Node {
public:
    // Methods
    void write_output(Frame to_write);
    void write_to_socket(Frame to_write);
    void send_acknowledgement(Frame to_ack);
    Frame read_from_socket();
    Frame read_from_input();
    bool is_mine(Frame to_check);
    void set_port(unsigned short port);
    void handle_frame(Frame frame);
    void send_loop();
    void receive_loop();

    // Constructors
    Node(uint8_t num) : _num {num}, _infile(("Node" + std::to_string((unsigned int) num) + "Input.txt").c_str()), _outfile(("Node" + std::to_string((unsigned int) num) + "Output.txt").c_str()) {};
    Node(const Node&) = delete;
    Node(Node&&) = delete;
protected:
    uint8_t _num;
    std::ifstream _infile;
    std::ofstream _outfile;
    TCPSocket *_switch_socket;
    bool _ack;
};
