/**
 * Switch.cpp
 * Part of CSE353, Project 2 by Ian Neal and Sean Turner
 */

#include "Switch.h"

namespace FreeLunch {

namespace Always {

template <typename T>
void sync_queue<T>::put(const T &val) {
  std::lock_guard<std::mutex> lck{mtx};
  q.push_back(val);
  cond.notify_all();
}

template <typename T>
void sync_queue<T>::get(T &val) {
  std::unique_lock<std::mutex> lck{mtx};
  cond.wait(lck,[this]{ return !q.empty(); });
  val = q.front();
  q.pop_front();
}

template <typename T>
void sync_queue<T>::peek(T &val) {
  std::unique_lock<std::mutex> lck{mtx};
  cond.wait(lck,[this]{ return !q.empty(); });
  val = q.front();
}

} // namespace Always

} // namespace FreeLunch