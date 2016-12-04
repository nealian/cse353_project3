#pragma once

#include <string>
#include <vector>
#include <memory>
#include "AtomicWriter.h"
#include "PracticalSocket.h"

class Hub {
public:
  std::string serv_addr = "127.0.0.1";
  uint16_t default_port = 5642;
  AtomicWriter w;

  Hub();
  Hub(const Hub&) = delete;
  Hub(Hub&&) = delete;

  void handle_new_connection();
  void handle_client(std::shared_ptr<TCPSocket> sock);
  void receive_loop(std::shared_ptr<TCPSocket> sock);

protected:
  std::vector<std::shared_ptr<TCPSocket>> nodes;
  std::vector::size_type active_node;
};