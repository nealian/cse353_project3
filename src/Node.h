#pragma once

#include "PracticalSocket.h"
#include "StarFrame.h"
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
  void write_output(StarFrame to_write);
  void write_to_socket(StarFrame to_write);
  void send_acknowledgement(StarFrame to_ack);
  StarFrame read_from_socket() throw (NodeException);
  StarFrame read_from_input();
  bool is_mine(StarFrame to_check);
  void set_port(unsigned short port);
  void handle_frame(StarFrame frame);
  void send_loop();
  void receive_loop();
  void set_finished();

  // Constructors
  Node(uint8_t num, unsigned short switch_tcp_port);
  Node(const Node&) = delete;
  Node(Node&&) = delete;
protected:
  const uint8_t _num;
  std::ifstream _infile;
  std::ofstream _outfile;
  TCPSocket * _switch_socket;
  bool _ack;
  static bool _all_finished;
};
