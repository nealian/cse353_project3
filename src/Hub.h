#pragma once

#include <string>
#include <vector>
#include <memory>
#include <mutex>
#include "AtomicWriter.h"
#include "PracticalSocket.h"


class HubConnectionList {
public:
  std::shared_ptr<TCPSocket> right_port(int num);
  void add(std::shared_ptr<TCPSocket> sock);
  void remove(int num);
  std::shared_ptr<TCPSocket> operator[](std::vector<std::shared_ptr<TCPSocket>>::size_type n);

  HubConnectionList() {};
private:
  std::vector<std::shared_ptr<TCPSocket>> _list;
  std::mutex _list_mtx;
};

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
  HubConnectionList connections;
};
