## Star and Ring Network Simulator

Written by Ian Neal and Sean Turner in C++ for NMT's CSE353 Fall 2016

### Building
`mkdir bin && cd bin && cmake .. && make`

### Running
`StarRingNetworkSimulator` (or `StarRingNetworkSimulator.exe`)

### Files
* `lib/` -- includes the PracticalSocket C++ library
* `src/` -- includes our written source code
  * `StarRingNetworkSimulator.h` and `StarRing
  NetworkSimulator.cpp` -- Main class code
  * `Frame.h` and `Frame.cpp` -- Frame class code
  * `Node.h` and `Node.cpp` -- Node class code
  * `Switch.h` and `Switch.cpp` -- Switch class and supporting types
  * `Hub.h` and `Hub.cpp` -- Hub class and supporting types
* `CMakeLists.txt` -- CMake build specifications
* `bin/` -- created by the build step, contains cmake files, makefile, executables, and intermediates

### Feature Checklist

| Feature                                                                                    | Status/Description           |
| ------------------------------------------------------------------------------------------ | ---------------------------- |
| Project compiles and builds without warnings or errors                                     | Complete                     |
| Switch class                                                                               | Incomplete                   |
| Switch has a frame buffer, and reads/writes appropriately                                  | Complete                     |
| Switch allows multiple connections                                                         | Complete?                    |
| Switch floods frame when it doesn't know the destination                                   | Complete                     |
| Switch learns destinations, and doesn't forward packet to any port except the one req'd    | Complete?                    |
| Node class                                                                                 | Incomplete                   |
| Nodes instantiate, and open connection to the switch                                       | Complete?                    |
| Nodes open their input files, and send data to switch                                      | Complete?                    |
| Nodes open their output files and save data that they received                             | Complete?                    |
| Node connects to both switch and hub                                                       | Incomplete                   |
| Node differentiates traffic between two networks based on traffic type                     | Incomplete                   |
| Node will sometimes drop acknowledgement                                                   | Incomplete                   |
| Node will sometimes create erroneous frame                                                 | Incomplete                   |
| Node will sometimes reject traffic                                                         | Incomplete                   |
| Node will fall back on star network when hub fails                                         | Incomplete                   |
| Node will fall back on ring network when switch fails                                      | Incomplete                   | 
| Hub                                                                                        | Incomplete                   |
| Hub passes traffic sequentially                                                            | Incomplete                   |
| Hub will drain erroneous frames                                                            | Incomplete                   |
| Hub will create a new token if lost                                                        | Incomplete                   |

### Known Bugs
* Star network still doesn't work right. No output files get written
* `Frame.cpp:49` throws out-of-range exceptions due to the substring stuff
*