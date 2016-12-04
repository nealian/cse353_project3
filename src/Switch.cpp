/**
 * Switch.cpp
 * Part of CSE353, Project 2 by Ian Neal and Sean Turner
 */

#include "Switch.h"

template <typename T>
void sync_queue<T>::put(const T &val) {
  std::lock_guard<std::mutex> lck{mtx};
  q.push(val);
  cond.notify_all();
}

template <typename T>
void sync_queue<T>::put(const T&& val) {
  std::lock_guard<std::mutex> lck{mtx};
  q.push(*val);
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
T sync_queue<T>::get() {
  std::unique_lock<std::mutex> lck{mtx};
  cond.wait(lck,[this]{ return !q.empty(); });
  T ret = q.top();
  q.pop();
  return ret;
}

template <typename T>
void sync_queue<T>::peek(T &val) {
  std::unique_lock<std::mutex> lck{mtx};
  cond.wait(lck,[this]{ return !q.empty(); });
  val = q.top();
}



/* Switch class */
Switch::Switch() {

  std::thread queue_thread(&Switch::process_queue, this);
  queue_thread.detach();

  while (not this->transmissions_complete) {
    Switch::handle_new_connection();
  }
}

void Switch::handle_new_connection() {
  try {
    TCPServerSocket default_sock(this->default_port);
    std::shared_ptr<TCPSocket> new_sock(default_sock.accept());
/*
    std::future<void> fut = std::async(std::launch::async, // ensures a separate thread is spawned
      Switch::handle_client, // handle to function we want to call
      new_sock); // arg to that function

    _futures.push_back(fut);
*/

    std::thread new_client_thread(&Switch::handle_client, this, new_sock);
    new_client_thread.detach();

  } catch (SocketException& e) {
    w << e.what() << std::endl;
  }

}

void Switch::handle_client(std::shared_ptr<TCPSocket> sock) {
  AtomicWriter w;
  try {
    TCPServerSocket newserv(serv_addr, default_port);
    unsigned short my_port = (newserv.getLocalPort());
    std::ostringstream my_port_ostringstream;
    my_port_ostringstream << my_port;
    std::string my_port_as_string = my_port_ostringstream.str();

    while (not this->transmissions_complete) {

      sock->send(static_cast<const void *>(my_port_as_string.c_str()), my_port_as_string.length());
      sock->cleanUp(); // not sure if this destroys?

      std::shared_ptr<TCPSocket> newsock(newserv.accept());

      broadcast_sockets.push_back(newsock);
      std::thread receive_thread(&Switch::receive_loop, this, newsock);
      receive_thread.detach();
    }
  } catch (SocketException e) {
    w << e.what() << std::endl;
  }
}

void Switch::process_queue() {
  AtomicWriter w;
  try {
    while (not this->transmissions_complete) {
      if (!frame_buffer.empty()) {
        auto frame = frame_buffer.get();

        if (switch_table.count(frame.dst()) > 0) {
          auto dst_sock = switch_table[frame.dst()];
          // send to dst
          dst_sock.get()->send(static_cast<const void *>(frame.raw().c_str()), frame.size());
        } else {
          // broadcast
          for (auto b : this->broadcast_sockets) {
            b.get()->send(static_cast<const void *>(frame.raw().c_str()), frame.size());
          }
        }
      } else {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Sleep for half a second
      }
    }
  } catch (SocketException e) {
    w << e.what() << std::endl;
  }
}

void Switch::receive_loop(std::shared_ptr<TCPSocket> sock) {
  try {
    while (not this->transmissions_complete) {
      // Receive and handle frames, modifying broadcast_sockets and switch_table as necessary
      char buffer[MAX_STARFRAME_SZ+1];
      std::string buffer_string;
      sock->recv(buffer, MAX_STARFRAME_SZ);
      buffer_string = buffer;
      StarFrame newframe(buffer_string);

      if (switch_table.count(newframe.src()) == 0) { // Source not in switching table!
        switch_table.insert(std::make_pair(newframe.src(), sock));
        std::vector<std::shared_ptr<TCPSocket>>::iterator i = std::find(broadcast_sockets.begin(), broadcast_sockets.end(), sock);
        broadcast_sockets.erase(i);
      }

      frame_buffer.put(newframe);
    }

  } catch (SocketException e) {
    w << e.what() << std::endl;
  }
}
