#include <uv.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>

#include <uvpp/GlobalLoop.hpp>

#include "networking/Server.hpp"
#include "networking/Socket.hpp"
#include "networking/ServerStartException.hpp"

using string = std::string;
using SocketContainer = std::shared_ptr<networking::Socket>;
using OnConnectionCallback = std::function<void (SocketContainer)>;

const int DEFAULT_BACKLOG = 128;

void networking::Server::onConnection(OnConnectionCallback callback) {
  connectionEventHandlers.push_back(callback);
}

void networking::Server::clearClosedSockets() {
  auto it = std::copy_if(
    clientSockets.begin(),
    clientSockets.end(),
    clientSockets.begin(),
    [](SocketContainer socket) {
      return !socket->isClosed();
    }
  );
  clientSockets.resize(std::distance(clientSockets.begin(), it));
}

void networking::Server::libuvOnConnection(uv_stream_t *stream, int status) {
  auto server = static_cast<networking::Server*>(stream->data);

  if (status < 0) {
    for (auto listener : server->onErrorHandlers) {
      listener(status);
    }
    return;
  }

  server->clearClosedSockets();

  SocketContainer socket(new Socket());
  server->clientSockets.push_back(socket);

  uv_tcp_init(server->loop, &socket->handle);
  socket->handle.data = &(*socket);

  if (uv_accept(stream, (uv_stream_t*) &socket->handle) == 0) {
    for (auto eventHandler : server->connectionEventHandlers) {
      eventHandler(socket);
    }
    uv_read_start(
      (uv_stream_t*) &socket->handle,
      networking::Socket::allocBuffer,
      networking::Socket::libuvOnRead
    );
  } else {
    uv_close((uv_handle_t*) &socket->handle, NULL);
  }
}

networking::ListenResult::ListenResult() {
  failed = false;
}

networking::ListenResult::ListenResult(ServerStartException error) {
  failed = true;
  this->error = error;
}

networking::ListenResult networking::Server::listen(string host, int port) {
  return listen(host, port, uvpp::GlobalLoop::getUVLoop());
}

networking::ListenResult networking::Server::listen(
  string host,
  int port,
  uv_loop_t *loop
) {
  this->loop = loop;

  uv_tcp_init(loop, &this->socket.handle);
  this->socket.handle.data = this;

  struct sockaddr_in addr;
  uv_ip4_addr(host.c_str(), port, &addr);
  uv_tcp_bind(&this->socket.handle, (const struct sockaddr*) &addr, 0);

  ListenResult result;

  int r = uv_listen(
    (uv_stream_t*) &this->socket.handle,
    DEFAULT_BACKLOG,
    networking::Server::libuvOnConnection
  );
  if (r) {
    ServerStartException exception(uv_strerror(r));
    result = ListenResult(exception);
    return result;
  }

  return result;
}
