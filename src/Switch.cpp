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
  val = q.front();
  q.pop();
}

template <typename S, typename T>
void sync_queue<S, T>::peek(Tuple<S, T> &val) {
  std::unique_lock<std::mutex> lck{mtx};
  cond.wait(lck,[this]{ return !q.empty(); });
  val = q.front();
}

void Switch::handle_new_connection() {
  try {
    this->default_sock(this->default_port);
  } catch (SocketException& e) {
    w << e.what() << std::endl;
  }

}

} // namespace Always

} // namespace FreeLunch