## Star Network Simulator

Written by Ian Neal and Sean Turner in C++ for NMT's CSE353 Fall 2016

### Building
`mkdir bin && cd bin && cmake .. && make`

### Running
`StarNetworkSimulator` (or `StarNetworkSimulator.exe`)

### Files
* `lib/` -- includes the PracticalSocket C++ library
* `src/` -- includes our written source code
  * `StarNetworkSimulator.h` and `StarNetworkSimulator.cpp` -- Main class code
  * `Frame.h` and `Frame.cpp` -- Frame class code
  * `Node.h` and `Node.cpp` -- Node class code
  * `Switch.h` and `Switch.cpp` -- Switch class and supporting types
* `CMakeLists.txt` -- CMake build specifications
* `bin/` -- created by the build step, contains cmake files, makefile, executables, and intermediates

### Feature Checklist
| Feature                                                                                    | Status/Description           |
| ------------------------------------------------------------------------------------------ | ---------------------------- |
| Project compiles and builds without warnings or errors                                     | Complete                     |
| Switch class                                                                               | Complete                     |
| Switch has a frame buffer, and reads/writes appropriately                                  | Complete                     |
| Switch allows multiple connections                                                         | Complete                     |
| Switch floods frame when it doesn't know the destination                                   | Complete                     |
| Switch learns destinations, and doesn't forward packet to any port except the one required | Complete                     |
| Node class                                                                                 | Complete                     |
| Nodes instantiate, and open connection to the switch                                       | Complete                     |
| Nodes open their input files, and send data to switch                                      | Complete                     |
| Nodes open their output files, and save data that they received                            | Complete                     |
| Main class                                                                                 | Complete                     |
| Frames can have priority                                                                   | Mostly complete -- the nodes' input doesn't distinguish priority, and neither does the nodes' input processing |

### Known Bugs
* No known bugs at this time