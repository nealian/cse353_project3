#pragma once

#include <string>
#include <vector>
#include <memory>
#include "PracticalSocket.h"

class Hub {
public:
  std::string serv_addr = "127.0.0.1";
  uint16_t default_port = 5642;

  Hub();
  Hub(const Hub&) = delete;
  Hub(Hub&&) = delete;

  void handle_new_connection();

protected:
  std::vector<std::shared_ptr<TCPSocket>> nodes;
  size_t active_node;
};