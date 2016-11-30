#pragma once

#include <string>
#include <cstdint>

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

  // Setters
  void ack();

  // Constructors
  RingFrame(std::string contents);
  RingFrame(bool tok);
  RingFrame(uint8_t src, uint8_t dst, std::string data, uint8_t priority) :
      _SRC{src}, _DST{dst}, _DATA{data}, _priority{priority} {};
  RingFrame(uint8_t src, uint8_t dst, std::string data) : RingFrame(src, dst, data, 0) {};
  RingFrame(const RingFrame &) = default; // For function parameters
  RingFrame(RingFrame &&) = default; // For function return values

  // Operators
  bool operator<(const RingFrame f2) const {return _priority < f2._priority;};
  RingFrame& operator=(const RingFrame&) = default;

protected:
  bool _tok = false;
  uint8_t _SRC;
  uint8_t _DST;
  std::string _DATA;
  uint8_t _priority;
  bool _ack;
};
