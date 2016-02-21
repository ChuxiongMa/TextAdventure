#include <iostream>

#include <uv.h>
#include <networking/Server.hpp>
#include <networking/ServerStartException.hpp>
#include <uvpp/GlobalLoop.hpp>

using namespace std;

using Server = networking::Server;
using ServerStartException = networking::ServerStartException;
using ListenResult = networking::ListenResult;
using SocketContainer = std::shared_ptr<networking::Socket>;
using OnConnectionCallback = std::function<void (SocketContainer)>;

int main() {
  uvpp::GlobalLoop::initializeLoop();

  const string host = "0.0.0.0";
  const int port = 5000;

  Server server;
  ListenResult result = server.listen(host, port);
  if (result.failed) {
    cerr << result.error.what() << endl;
    return 1;
  }
  server.onConnection(
    [](SocketContainer socket) {
      std::cout << "Got connection!" << std::endl;
      socket->onRead([socket](std::vector<unsigned char> packet) {
        std::cout << socket->getPeername().peername.address << " ";
        std::cout << socket->getPeername().peername.port << " ";
        std::cout << std::string(packet.begin(), packet.end()) << std::endl;
        socket->write(packet);
      });
      socket->onClose([]() {
        std::cout << "Socket closed" << std::endl;
      });
    }
  );
  cout << "Bound to " << host << " and listening on " << port << endl;

  return uvpp::GlobalLoop::runLoop();
}
