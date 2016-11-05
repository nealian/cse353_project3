/**
 * Switch.cpp
 * Part of CSE353, Project 2 by Ian Neal and Sean Turner
 */

#include "Switch.h"

namespace FreeLunch {

namespace Always {

template <typename S, typename T>
void sync_queue<S, T>::put(const T &val) {
  std::lock_guard<std::mutex> lck{mtx};
  q.push(val);
  cond.notify_all();
}

template <typename S, typename T>
void sync_queue<S, T>::get(T &val) {
  std::unique_lock<std::mutex> lck{mtx};
  cond.wait(lck,[this]{ return !q.empty(); });
  val = q.front();
  q.pop();
}

template <typename S, typename T>
void sync_queue<S, T>::peek(T &val) {
  std::unique_lock<std::mutex> lck{mtx};
  cond.wait(lck,[this]{ return !q.empty(); });
  val = q.front();
}

} // namespace Always

} // namespace FreeLunch