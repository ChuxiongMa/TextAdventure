#ifndef ISOCKET_H
#define ISOCKET_H

#include "IByteBufferAcceptor.hpp"
#include "ISender.hpp"

using ISender = pipeable::ISender;
using IByteBufferAcceptor = pipeable::IByteBufferAcceptor;

namespace pipeable {
  class ISocket: public ISender, public IByteBufferAcceptor {
  public:
    
  };
}

#endif
