#pragma once

#include <string>
#include <cstdint>

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
    Frame(uint8_t src, uint8_t dst, std::string data): _SRC {src}, _DST {dst}, _DATA {data} {};
    Frame(const Frame&) = delete;
    Frame(Frame&&) = delete;

protected:
    uint8_t _SRC;
    uint8_t _DST;
    std::string _DATA;
};
