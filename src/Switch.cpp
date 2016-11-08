/**
 * Switch.cpp
 * Part of CSE353, Project 2 by Ian Neal and Sean Turner
 */

#include "Switch.h"

template <typename T>
void sync_queue<T>::put(const T &val) {
  std::lock_guard<std::mutex> lck{mtx}; // TODO what is this for?
  q.push(val);
  cond.notify_all();
}

template <typename T>
void sync_queue<T>::put(const T& val) {
  std::lock_guard<std::mutex> lck{mtx};
  q.push(val);
  cond.notify_all();
}

template <typename T>
void sync_queue<T>::get(T &val) {
  std::unique_lock<std::mutex> lck{mtx};
  cond.wait(lck,[this]{ return !q.empty(); });
  val = q.top();
  q.pop();
}

template <typename T>
void sync_queue<T>::peek(T &val) {
  std::unique_lock<std::mutex> lck{mtx};
  cond.wait(lck,[this]{ return !q.empty(); });
  val = q.top();
}

void Switch::handle_new_connection() {
  try {
    TCPServerSocket default_sock(this->default_port);
    std::future<Frame> fut = std::async(std::launch::async, // ensures a separate thread is spawned
      Switch::handle_client, // handle to function we want to call
      std::unique_ptr<TCPSocket>(default_sock.accept())); // arg to that function

    _futures.push_back(fut);



  } catch (SocketException& e) {
    w << e.what() << std::endl;
  }

}

void Switch::handle_client(std::unique_ptr<TCPSocket> sock) {
  AtomicWriter w;
  try {
    TCPSocket newsock(serv_addr, default_port);
    unsigned short my_port = (newsock.getForeignPort());
    std::ostringstream my_port_ostringstream;
    my_port_ostringstream << my_port;
    std::string my_port_as_string = my_port_ostringstream.str();

    sock->send(static_cast<void *>(my_port_as_string.c_str()), my_port_as_string.length());
    sock->cleanUp(); // not sure if this destroys?

  } catch (SocketException e) {
    w << e.what() << std::endl;
  }
}

void Switch::listener() {
  AtomicWriter w;
  try {
    // stuff
  } catch (SocketException e) {
    w << e.what() << std::endl;
  }
}