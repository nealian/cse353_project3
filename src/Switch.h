/**
 * Switch.h
 * Part of CSE353, Project 2 by Ian Neal and Sean Turner
 */

#pragma once

#include <condition_variable>
#include <fstream>
#include <unordered_map>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>
#include <queue>
#include <algorithm>
#include "AtomicWriter.h"
#include "StarFrame.h"
#include "PracticalSocket.h"

// TODO: rewrite this queue to be lockfree if we have time
/**
 * from Stroustrup section 42.3.4
 */
template <typename T>
class sync_queue {
public:
  void put(const T& val);
  void put(const T&& val);
  void get(T& val);
  T get();
  void peek(T& val);
  bool empty() { return q.empty(); }
private:
  std::mutex mtx;
  std::condition_variable cond;
  std::priority_queue<T> q;
};



class Switch {
public:
  bool transmissions_complete = false;
  std::string serv_addr = "127.0.0.1";
  uint16_t default_port = 5643;
  AtomicWriter w;

  Switch();
  Switch(const Switch&) = delete;
  Switch(Switch&&) = delete;

  void handle_new_connection();
  void process_queue();
  void handle_client(std::shared_ptr<TCPSocket> sock);
  void receive_loop(std::shared_ptr<TCPSocket> sock);

protected:
  sync_queue<StarFrame> frame_buffer;
  std::unordered_map<uint8_t, std::shared_ptr<TCPSocket>> switch_table;
  std::vector<std::shared_ptr<TCPSocket>> broadcast_sockets;
private:
  std::mutex _switch_mtx;
  std::condition_variable _switch_cond;
};
