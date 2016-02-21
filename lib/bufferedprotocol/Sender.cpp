#include <bufferedprotocol/Sender.hpp>
#include <string>
#include <vector>

bufferedprotocol::Sender::Sender(): acceptor(nullptr) {}

bufferedprotocol::Sender::Sender(pipeable::IByteBufferAcceptor& acceptor)
  : acceptor(&acceptor) {}

  bufferedprotocol::Sender::Sender(pipeable::IByteBufferAcceptor* acceptor)
    : acceptor(acceptor) {}

void bufferedprotocol::Sender::write(const std::vector<unsigned char> &packet) {
  int size = packet.size();

  std::vector<unsigned char> toSend;

  toSend.push_back(size & 0xff);
  toSend.push_back((size >> 8) & 0xFF);
  toSend.push_back((size >> 16) & 0xFF);

  toSend.insert(toSend.end(), packet.begin(), packet.end());

  acceptor->write(toSend);
}

void bufferedprotocol::Sender::write(const std::string& str) {
  std::vector<unsigned char> packet(str.begin(), str.end());
  write(packet);
}
