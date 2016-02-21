#include <bufferednetworking/BufferedSocket.hpp>
#include <bufferedprotocol/Sender.hpp>

using Sender = bufferedprotocol::Sender;

bufferednetworking::BufferedSocket::BufferedSocket() {}

bufferednetworking::BufferedSocket::BufferedSocket(Socket& socket)
  : sender(Sender(socket))
  , socket(&socket) {}

bufferednetworking::BufferedSocket::BufferedSocket(Socket* socket)
  : sender(Sender(socket))
  , socket(socket) {}

void bufferednetworking::BufferedSocket::write(
  const std::vector<unsigned char>& packet
) {
  bufferer.write(packet);
}

void bufferednetworking::BufferedSocket::write(const std::string& packet) {
  bufferer.write(packet);
}

void bufferednetworking::BufferedSocket::send(
  const std::vector<unsigned char>& packet
) {
  sender.write(packet);
}

void bufferednetworking::BufferedSocket::send(
  const std::string& packet
) {
  sender.write(packet);
}

PeernameResult bufferednetworking::BufferedSocket::getPeername() {
  return socket->getPeername();
}

void bufferednetworking::BufferedSocket::onRead(
  std::function<void(const std::vector<unsigned char>&)> callback
) {
  bufferer.onCompletePacket(callback);
}

void bufferednetworking::BufferedSocket::onClose(std::function<void (void)> callback) {
  socket->onClose(callback);
}
