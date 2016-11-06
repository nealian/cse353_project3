#pragma once

#include <string>
#include <cstdint>

#define MAX_FRAME_SZ 258 // 1 byte for each SRC, DST, and SIZE/ACK, and 255 bytes for DATA.

class Frame {
public:
    // Getters
    uint8_t src();
    uint8_t dst();
    uint8_t size();
    std::string data();
    std::string raw();

    // Setters
    void clear();

    // Constructors
    Frame(std::string contents);
    Frame(uint8_t src, uint8_t dst, std::string data): _SRC {src}, _DST {dst}, _DATA {data}, _priority {0} {};
    Frame(uint8_t src, uint8_t dst, std::string data, uint8_t priority) : _SRC {src}, _DST {dst}, _DATA {data}, _priority {priority} {}
    Frame(const Frame&) = delete;
    Frame(Frame&&) = default;

    // Operators
    bool operator <(const Frame f2);

protected:
    uint8_t _SRC;
    uint8_t _DST;
    std::string _DATA;
    uint8_t _priority;
};
