/**
 * Switch.h
 * Part of CSE353, Project 2 by Ian Neal and Sean Turner
 */

#pragma once

// trim this down later;
#include <atomic>
#include <cerrno>
#include <condition_variable>
#include <cstring>
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <queue>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <queue>
#include <sys/types.h>
#include <sys/socket.h>
#include "Frame.h"
#include "PracticalSocket.h"

const int RCVBUFSIZE = 2048;

class Switch {
public:
  bool frame_buf_flag = false;
  std::string serv_addr = "127.0.0.1";
  uint8_t default_port = 0;
  AtomicWriter w;

  void handle_new_connection();
  void process_queue();
  void handle_client(std::unique_ptr<TCPSocket> sock);
  void receive_loop(TCPSocket &sock);

protected:
  sync_queue<Frame> frame_buffer;
  // <port, _num>? This may need to change.
  std::unordered_map<uint8_t, TCPSocket &> switch_table;
  std::vector<TCPSocket &> broadcast_sockets;
private:
  std::mutex _switch_mtx;
  std::condition_variable _switch_cond;
  std::vector<std::future<Frame>> _futures;
};

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
  Frame get();
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