#include <functional>
#include <iostream>

#include <uv.h>
#include <uvpp/GlobalLoop.hpp>

#include "networking/Client.hpp"
#include "networking/Socket.hpp"

void networking::Client::libuvOnConnect(uv_connect_t *req, int status) {
  networking::Client* client = static_cast<networking::Client*>(req->data);

  if (status < 0) {
    for (auto listener : client->onErrorListeners) { listener(status); }
    return;
  }

  client->socket.handle.data = &client->socket;

  for (auto listener : client->onConnectListeners) { listener(); }

  uv_read_start(
    (uv_stream_t*) &client->socket.handle,
    networking::Socket::allocBuffer,
    networking::Socket::libuvOnRead
  );
}

networking::Socket* networking::Client::getSocket() { return &socket; }

void networking::Client::onConnect(std::function<void (void)> listener) {
  onConnectListeners.push_back(listener);
}

void networking::Client::onError(std::function<void (int)> listener) {
  onErrorListeners.push_back(listener);
}

void networking::Client::connect(string host, int port) {
  connect(host, port, uvpp::GlobalLoop::getUVLoop());
}

void networking::Client::connect(string host, int port, uv_loop_t* loop) {
  this->connection.data = this;

  struct sockaddr_in requestAddress;
  uv_ip4_addr(host.c_str(), port,  &requestAddress);

  uv_tcp_init(loop, &this->socket.handle);
  uv_tcp_keepalive(&this->socket.handle, 1, 60);
  uv_tcp_connect(
    &this->connection,
    &this->socket.handle,
    (const struct sockaddr*) &requestAddress,
    networking::Client::libuvOnConnect
  );
}
