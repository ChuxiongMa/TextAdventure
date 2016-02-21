#ifndef SENDER_H
#define SENDER_H

#include <functional>
#include <string>

#include <pipeable/IByteBufferAcceptor.hpp>

namespace bufferedprotocol {

  /**
   * This is the helper class for prepending byte buffer sizes, right before
   * sending a byte stream payload.
   */
  class Sender: public pipeable::IByteBufferAcceptor {
    pipeable::IByteBufferAcceptor* acceptor;
  public:
    Sender();
    Sender(pipeable::IByteBufferAcceptor&);
    Sender(pipeable::IByteBufferAcceptor*);
    void write(const std::vector<unsigned char>&);
    void write(const std::string& str);
  };
}

#endif
