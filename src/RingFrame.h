#pragma once

#include <string>
#include <cstdint>
#include <vector>

#define MAX_RINGFRAME_SZ 262 // 1 byte for each AC, FC, SRC, DST, and SIZE, 255 bytes for DATA, and 1
  // byte for each CRC and FS

class RingFrame {
public:
  // Getters
  bool tok();
  uint8_t src();
  uint8_t dst();
  uint8_t size();
  std::string data();
  std::string raw();
  uint8_t crc();

  // Setters
  void ack();

  // Constructors
  RingFrame(std::string contents);
  RingFrame(bool tok) : _tok {tok} {}; // Generates a token-only frame
  RingFrame(uint8_t src, uint8_t dst, std::string data, uint8_t priority) :
      _SRC{src}, _DST{dst}, _DATA{data} {};
  RingFrame(uint8_t src, uint8_t dst, std::string data) : RingFrame(src, dst, data, 0) {};

  RingFrame(const RingFrame &) = default; // For function parameters
  RingFrame(RingFrame &&) = default; // For function return values

  // Operators
  bool operator<(const RingFrame f2) const {return _DATA.length() < f2._DATA.length();};
  RingFrame& operator=(const RingFrame&) = default;

protected:
  bool _tok = false;
  uint8_t _SRC;
  uint8_t _DST;
  std::string _DATA;
  bool _ack;

private:
  std::string raw_no_crc();
};
