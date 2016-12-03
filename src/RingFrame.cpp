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

std::string RingFrame::raw_no_crc() {
  if (_tok) {
    std::string ac_fc_raw(1, 1);

    return ac_fc_raw + ac_fc_raw;
  } else {
    std::string zero_as_string(1, 0);
    std::string src_raw(1, (char) _SRC); // Using the fill(n, char) constructor
    std::string dst_raw(1, (char) _DST);
    std::string size_raw(1, (char) size());

    return zero_as_string + zero_as_string + dst_raw + src_raw + size_raw + _DATA;
  }
}

uint8_t RingFrame::crc() {
  auto raw_str = raw_no_crc();

  std::vector<unsigned char> bytes(raw_str.begin(), raw_str.end());

  uint8_t crc = 0;

  for (auto b : bytes) {
    crc += b;
  }

  return crc;
}

std::string RingFrame::raw() {
  std::string ack_raw(1, (char) _ack ? 3 : 0);
  std::string crc_raw(1, (char) crc());
  return raw_no_crc() + crc_raw + ack_raw + "\n";
}


/* Setters */
void RingFrame::ack() {
  _ack = true;
}


/* Constructors */
RingFrame::RingFrame(std::string contents) {
  _SRC = (uint8_t) contents[0];
  _DST = (uint8_t) contents[1];
  _DATA = contents.substr(3, (size_t) contents[2]);
}