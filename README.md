## Star Network Simulator

Written by Ian Neal and Sean Turner in C++ for NMT's CSE353 Fall 2016

### Building
`ccmake . && make`

### Running
`StarNetworkSimulator` (or `StarNetworkSimulator.exe`)

### Files
* `lib/` -- includes the PracticalSocket C++ library
* `src/` -- includes our written source code
  * `StarNetworkSimulator.h` and `StarNetworkSimulator.cpp` -- our code
* `CMakeLists.txt` -- CMake build specifications

### Feature Checklist
| Feature                                                                                    | Status/Description           |
| ------------------------------------------------------------------------------------------ | ---------------------------- |
| Project compiles and builds without warnings or errors                                     | Incomplete                   |
| Switch class                                                                               | Incomplete                   |
| Switch has a frame buffer, and reads/writes appropriately                                  | Incomplete                   |
| Switch allows multiple connections                                                         | Incomplete                   |
| Switch floods frame when it doesn't know the destination                                   | Incomplete                   |
| Switch learns destinations, and doesn't forward packet to any port except the one required | Incomplete                   |
| Node class                                                                                 | Incomplete                   |
| Nodes instantiate, and open connection to the switch                                       | Incomplete                   |
| Nodes open their input files, and send data to switch                                      | Incomplete                   |
| Nodes open their output files, and save data that they received                            | Incomplete                   |

### Known Bugs
* No known bugs at this time