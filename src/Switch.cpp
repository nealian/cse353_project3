/**
 * Switch.cpp
 * Part of CSE353, Project 2 by Ian Neal and Sean Turner
 */

#include "Switch.h"

namespace FreeLunch {

namespace Always {

template <typename S, typename T>
void sync_queue<S, T>::put(const Tuple<S, T> &val) {
  std::lock_guard<std::mutex> lck{mtx};
  q.push(val);
  cond.notify_all();
}

template <typename S, typename T>
void sync_queue<S, T>::put(const T& val) {
  std::lock_guard<std::mutex> lck{mtx};
  S priority = new S();
  Tuple<S, T> to_push = { priority, val };
  q.push(to_push);
  cond.notify_all();
}

template <typename S, typename T>
void sync_queue<S, T>::get(Tuple<S, T> &val) {
  std::unique_lock<std::mutex> lck{mtx};
  cond.wait(lck,[this]{ return !q.empty(); });
  val = q.top();
  q.pop();
}

template <typename S, typename T>
void sync_queue<S, T>::peek(Tuple<S, T> &val) {
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
    sock->getForeignAddress();
  } catch (SocketException e) {
    w << e.what() << std::endl;
  }

  if (_switch_mtx.try_lock()) {
    char buffer[RCVBUFSIZE];
    int msg_size;

    while ((msg_size = sock->recv(buffer, RCVBUFSIZE)) > 0) {
      sock->
      /// do things here...
    }
  }
}

} // namespace Always

} // namespace FreeLunch