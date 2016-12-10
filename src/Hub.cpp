#include "Hub.h"
#include <thread>
#include <sstream>


std::shared_ptr<TCPSocket> HubConnectionList::right_port(int num) {
  _list_mtx.lock();
  std::shared_ptr elem;
  if (num > _list.size()) {
    elem = _list[num % _list.size()];
  } else {
    elem = _list[num];
  }
  _list_mtx.unlock();
  return elem;
}

void HubConnectionList::add(std::shared_ptr<TCPSocket> sock) {
  _list_mtx.lock();
  int num = _list.size() + 1;
  _list.push_back(sock);
  _list_mtx.unlock();
}

void HubConnectionList::remove(int num) {
  _list_mtx.lock();
  _list.erase(_list.begin() + num);
  _list_mtx.unlock();
}

std::shared_ptr<TCPSocket> HubConnectionList::operator[](std::vector<std::shared_ptr<TCPSocket>>::size_type n) {
  _list_mtx.lock();
  std::shared_ptr<TCPSocket> elem = _list[n];
  _list_mtx.unlock();
  return elem;
}


/* HUB */
void Hub::handle_new_connection() {
  try {
    TCPServerSocket default_sock(this->default_port);
    std::shared_ptr<TCPSocket> new_sock(default_sock.accept());

    std::thread new_client_thread(&Hub::handle_client, this, new_sock);
    new_client_thread.detach();

  } catch (SocketException& e) {
    w << e.what() << std::endl;
  }
}

void Hub::handle_client(std::shared_ptr<TCPSocket> sock) {
  try {
    // TODO
  } catch (SocketException e) {
    w << e.what() << std::endl;
  }
}

void Hub::receive_loop(std::shared_ptr<TCPSocket> sock) {
  // TODO
}
