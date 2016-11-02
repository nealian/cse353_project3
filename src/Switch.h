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
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <queue>
#include <arpa/inet.h>
#include <lib/PracticalSocket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

namespace FreeLunch { // ok I'm just being silly, we can get rid of this in prod :)

namespace Switch {

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
  void peek(T& val);
  bool empty() { return q.empty(); }
private:
  std::mutex mtx;
  std::condition_variable cond;
  list<T> q;
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

} // namespace Switch

} // namespace FreeLunch