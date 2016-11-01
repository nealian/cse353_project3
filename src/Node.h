#pragma once

#include <cstdint>
#include <string>
#include <fstream>

class Node {
public:
    // Methods
    void write_output(std::string to_write);

    // Constructors
    Node(uint8_t num) : _num {num}, _infile(("Node" + std::to_string(num) + "Input.txt").c_str()), _outfile(("Node" + std::to_string(num) + "Output.txt").c_str()) {};
    Node(const Node&) = delete;
    Node(Node&&) = delete;
protected:
    int _num;
    std::ifstream _infile;
    std::ofstream _outfile;
};
