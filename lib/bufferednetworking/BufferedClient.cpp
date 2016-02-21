#include <uvpp/GlobalLoop.hpp>

#include "bufferednetworking/BufferedClient.hpp"

bufferednetworking::BufferedClient::BufferedClient() {
  this->socket = BufferedSocket(client.getSocket());
}

void bufferednetworking::BufferedClient::connect(string host, int port) {
  connect(host, port, uvpp::GlobalLoop::getUVLoop());
}

void bufferednetworking::BufferedClient::connect(
  string host,
  int port,
  uv_loop_t* loop
) {
  client.onConnect([=]() {
    this->client.getSocket()->pipe(this->socket);
  });
  client.connect(host, port, loop);
}

void bufferednetworking::BufferedClient::onConnect(
  std::function<void (void)> callback
) {
  client.onConnect(callback);
}

void bufferednetworking::BufferedClient::onError(
  std::function<void (int err)> callback
) {
  client.onError(callback);
}

BufferedSocket* bufferednetworking::BufferedClient::getSocket() {
  return &socket;
}
