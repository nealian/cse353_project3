#include "StarFrame.h"

/* Getters */
uint8_t StarFrame::src() {
  return _SRC;
}

uint8_t StarFrame::dst() {
  return _DST;
}

uint8_t StarFrame::size() {
  return _DATA.length();
}

std::string StarFrame::data() {
  return _DATA;
}

std::string StarFrame::raw() {
  std::string src_raw(1, (char) _SRC); // Using the fill(n, char) constructor
  std::string dst_raw(1, (char) _DST);
  std::string size_raw(1, (char) size());

  if (_priority == 0) {
    return src_raw + dst_raw + size_raw + _DATA + "\n";
  } else {
    std::string priority_raw (1, (char) _priority);
    std::string zero_raw (1, 0);
    compute_crc();
    return raw_no_crc() + std::to_string(_crc) + "\n";
  }
}


/* Setters */
void StarFrame::clear() {
  _DATA.clear();
}


/* Constructors */
StarFrame::StarFrame(std::string contents) {
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

void StarFrame::compute_crc() {
  auto raw_str = raw_no_crc();

  std::vector<unsigned char> bytes(raw_str.begin(), raw_str.end());

  _crc = 0;

  for (auto b : bytes) {
    _crc += b;
  }
}

std::string StarFrame::raw_no_crc() {
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