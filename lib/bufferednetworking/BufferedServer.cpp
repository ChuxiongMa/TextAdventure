#include <uvpp/GlobalLoop.hpp>

#include "bufferednetworking/BufferedServer.hpp"

ListenResult bufferednetworking::BufferedServer::listen(
  string host,
  int port
) {
  return listen(host, port, uvpp::GlobalLoop::getUVLoop());
}

ListenResult bufferednetworking::BufferedServer::listen(
  string host,
  int port,
  uv_loop_t* loop
) {
  return server.listen(host, port, loop);
}

void bufferednetworking::BufferedServer::onConnection(
  std::function<void (BufferedSocket&)> callback
) {
  auto& proxies = this->proxies;
  server.onConnection(
    [&proxies, &callback](std::shared_ptr<Socket> socket) {
      proxies[socket] = BufferedSocket(*socket);

      // TODO: abstract this away.
      socket->pipe(proxies[socket]);
      socket->onClose([&proxies, &socket]() {
        proxies.erase(socket);
      });

      callback(proxies[socket]);
    }
  );
}
