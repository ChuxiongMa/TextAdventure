#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <functional>

#include <uv.h>
#include <uvpp/GlobalLoop.hpp>
#include <networking/Server.hpp>
#include <networking/ServerStartException.hpp>
#include <bufferedprotocol/Bufferer.hpp>
#include <bufferedprotocol/Sender.hpp>
#include <pipeable/IByteBufferAcceptor.hpp>
#include <bufferednetworking/BufferedServer.hpp>
#include <bufferednetworking/BufferedSocket.hpp>

using namespace std;

using Server = networking::Server;
using ServerStartException = networking::ServerStartException;
using ListenResult = networking::ListenResult;
using Bufferer = bufferedprotocol::Bufferer;
using Sender = bufferedprotocol::Sender;
using IByteBufferAcceptor = pipeable::IByteBufferAcceptor;
using Socket = networking::Socket;
using BufferedServer = bufferednetworking::BufferedServer;
using BufferedSocket = bufferednetworking::BufferedSocket;

int main() {
  uvpp::GlobalLoop::initializeLoop();

  const string host = "0.0.0.0";
  const int port = 5000;

  BufferedServer server;
  ListenResult result = server.listen(host, port);
  if (result.failed) {
    cerr << result.error.what() << endl;
    return 1;
  }
  server.onConnection(
    [](BufferedSocket& proxy) {
      std::cout << "Got connection!" << std::endl;
      proxy.onRead([&proxy](std::vector<unsigned char> packet) {
        std::cout << proxy.getPeername().peername.address << " ";
        std::cout << proxy.getPeername().peername.port << " ";
        std::cout << std::string(packet.begin(), packet.end()) << std::endl;
        proxy.write(packet);
      });
      proxy.onClose([]() {
        std::cout << "Socket closed" << std::endl;
      });
    }
  );
  cout << "Bound to " << host << " and listening on " << port << endl;
  return uvpp::GlobalLoop::runLoop();
}
