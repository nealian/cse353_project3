#include "RingFrame.h"

/* Getters */
bool RingFrame::tok() {
  return _tok;
}

uint8_t RingFrame::src() {
  return _SRC;
}

uint8_t RingFrame::dst() {
  return _DST;
}

uint8_t RingFrame::size() {
  return _DATA.length();
}

std::string RingFrame::data() {
  return _DATA;
}

std::string RingFrame::raw() { // TODO FIXME
  std::string src_raw(1, (char) _ack ? 1 : 0);
  std::string src_raw(1, (char) _SRC); // Using the fill(n, char) constructor
  std::string dst_raw(1, (char) _DST);
  std::string size_raw(1, (char) size());

  if (_priority == 0) {
    return src_raw + dst_raw + size_raw + _DATA + "\n";
  } else {
    std::string priority_raw (1, (char) _priority);
    std::string zero_raw (1, 0);

    return src_raw + zero_raw + size_raw + dst_raw + priority_raw + _DATA + "\n";
  }
}


/* Setters */
void RingFrame::ack() {
  _ack = true;
}


/* Constructors */
RingFrame::RingFrame(std::string contents) {
  _SRC = (uint8_t) contents[0];
  _DST = (uint8_t) contents[1];
  if(_DST == 0) {
    _DST = (uint8_t) contents[3];
    _priority = (uint8_t) contents[4];
    _DATA = contents.substr(5, (size_t) contents[2]);
  } else {
    _priority = 0;
    _DATA = contents.substr(3, (size_t) contents[2]);
  }
}