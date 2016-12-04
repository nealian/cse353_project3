#include "Hub.h"
#include <thread>
#include <sstream>


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

