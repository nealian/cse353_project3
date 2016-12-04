#pragma once

#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iostream>
#include "PracticalSocket.h"


/**
 * code from:
 * https://stackoverflow.com/questions/15033827/multiple-threads-writing-to-stdcout-or-stdcerr
 * to solve problems with threads writing to streams
 *
 * I used this to get around some weird problems in p1. Streams *should* be threadsafe,
 * but I'm throwing this in just in case.
 */
class AtomicWriter {
  std::ostringstream st;
  std::ostream &stream;
public:
  AtomicWriter(std::ostream &s=std::cout):stream(s) { }
  template <typename T>
  AtomicWriter& operator<<(T const& t) {
    st << t;
    return *this;
  }
  AtomicWriter& operator<<( std::ostream&(*f)(std::ostream&) ) {
    st << f;
    return *this;
  }
  ~AtomicWriter() { stream << st.str(); }
};



class Hub {
public:
  std::string serv_addr = "127.0.0.1";
  uint16_t default_port = 5642;

  Hub();
  Hub(const Hub&) = delete;
  Hub(Hub&&) = delete;

  void handle_new_connection();
  void receive_loop(std::shared_ptr<TCPSocket> sock);

protected:
  std::vector<std::shared_ptr<TCPSocket>> nodes;
  std::vector::size_type active_node;
};