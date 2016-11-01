#pragma once

#include <cstdint>
#include <string>
#include <fstream>

class Node {
public:

    // Constructors
    Node(uint8_t num) : _num {num} {};
    Node(const Node&) = delete;
    Node(Node&&) = delete;
protected:
    int _num;
    std::ifstream _infile;
    std::ofstream _outfile;
};