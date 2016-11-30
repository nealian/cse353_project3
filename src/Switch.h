/**
 * Switch.h
 * Part of CSE353, Project 2 by Ian Neal and Sean Turner
 */

#pragma once

// trim this down later;
//#include <atomic>
#include <algorithm>
#include <condition_variable>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <queue>
#include "Frame.h"
#include "PracticalSocket.h"

// TODO: rewrite this queue to be lockfree if we have time
/**
 * from Stroustrup section 42.3.4
 */
template <typename T>
class sync_queue {
public:
  void put(const T& val);
  void put(const T&& val);
  void get(T& val);
  T get();
  void peek(T& val);
  bool empty() { return q.empty(); }
private:
  std::mutex mtx;
  std::condition_variable cond;
  std::priority_queue<T> q;
};


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


class Switch {
public:
  bool transmissions_complete = false;
  std::string serv_addr = "127.0.0.1";
  uint16_t default_port = 5643;
  AtomicWriter w;

  Switch();
  Switch(const Switch&) = delete;
  Switch(Switch&&) = delete;

  void handle_new_connection();
  void process_queue();
  void handle_client(std::shared_ptr<TCPSocket> sock);
  void receive_loop(std::shared_ptr<TCPSocket> sock);

protected:
  sync_queue<Frame> frame_buffer;
  // <port, _num>? This may need to change.
  std::unordered_map<uint8_t, std::shared_ptr<TCPSocket>> switch_table;
  std::vector<std::shared_ptr<TCPSocket>> broadcast_sockets;
private:
  std::mutex _switch_mtx;
  std::condition_variable _switch_cond;
  //std::vector<std::future<Frame>> _futures;
};