#include "Frame.h"

/* Getters */
uint8_t Frame::src() {
  return _SRC;
}

uint8_t Frame::dst() {
  return _DST;
}

uint8_t Frame::size() {
  return _DATA.length();
}

std::string Frame::data() {
  return _DATA;
}

std::string Frame::raw() {
  std::string src_raw(1, (char) _SRC); // Using the fill(n, char) constructor
  std::string dst_raw(1, (char) _DST);
  std::string size_raw(1, (char) size());

  return src_raw + dst_raw + size_raw + _DATA;
}


/* Setters */
void Frame::clear() {
  _DATA.clear();
}


/* Constructors */
Frame::Frame(std::string contents) {
  _SRC = (uint8_t) contents[0];
  _DST = (uint8_t) contents[1];
  _DATA = contents.substr(3, (size_t) contents[2]);
}
