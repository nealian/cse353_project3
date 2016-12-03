#pragma once

#include <string>
#include <cstdint>
#include <vector>

#define MAX_FRAME_SZ 258 // 1 byte for each SRC, DST, and SIZE/ACK, 255 bytes for DATA, and 1 byte for CRC.

class StarFrame {
public:
  // Getters
  uint8_t src();
  uint8_t dst();
  uint8_t size();
  std::string data();
  std::string raw();
  uint8_t crc();

  // Setters
  void clear();

  // Constructors
  StarFrame(std::string contents);
  StarFrame(uint8_t src, uint8_t dst, std::string data, uint8_t priority) :
      _SRC{src}, _DST{dst}, _DATA{data}, _priority{priority} {};
  StarFrame(uint8_t src, uint8_t dst, std::string data) : StarFrame(src, dst, data, 0) {};
  StarFrame(const StarFrame &) = default; // For function parameters
  StarFrame(StarFrame &&) = default; // For function return values

  // Operators
  bool operator<(const StarFrame f2) const {return _priority < f2._priority;};
  StarFrame& operator=(const StarFrame&) = default;

protected:
  uint8_t _SRC;
  uint8_t _DST;
  std::string _DATA;
  uint8_t _priority;

private:
  std::string raw_no_crc();
};
