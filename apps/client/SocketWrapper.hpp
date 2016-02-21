#ifndef SOCKET_WRAPPER_H
#define SOCKET_WRAPPER_H

#include "IPacketAcceptor.hpp"

class SocketWrapper {
public:
  SocketWrapper(ISocket& socket) {

  }

  void setAcceptor(IPacketAcceptor* acceptor) {
    this->acceptor = acceptor;
  }
  void clearAcceptor() {
    this->acceptor = nullptr;
  }
private:
  IPacketAcceptor* acceptor;
};

#endif
