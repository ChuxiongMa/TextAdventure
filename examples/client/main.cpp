#include <iostream>

#include <uv.h>
#include <uvpp/GlobalLoop.hpp>

#include "networking/Client.hpp"

int main() {
  uvpp::GlobalLoop::initializeLoop();

  const string host = "127.0.0.1";
  const int port = 5000;

  networking::Client client;

  client.onConnect([&client]() {
    client.getSocket()->write("Hello");
  });

  client.getSocket()->onRead([&client](std::vector<unsigned char> packet) {
    std::cout << "Server response:" << std::endl;
    std::cout << std::string(packet.begin(), packet.end()) << std::endl;
  });

  client.connect(host, port);

  return uvpp::GlobalLoop::runLoop();
}
