set(CMAKE_BUILD_TYPE Debug)

add_executable(StarNetworkSimulator StarNetworkSimulator.cpp StarFrame.cpp RingFrame.cpp Node.cpp Switch.cpp)
set_property(TARGET StarNetworkSimulator PROPERTY CXX_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(StarNetworkSimulator LINK_PUBLIC PracticalSocket Threads::Threads)