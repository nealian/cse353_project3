#pragma once

#include <sstream>
#include <iostream>

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