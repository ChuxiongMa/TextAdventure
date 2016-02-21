#ifndef IBYTE_BUFFER_ACCEPTOR_H
#define IBYTE_BUFFER_ACCEPTOR_H

#include <vector>
#include <string>

namespace pipeable {
  class IByteBufferAcceptor {
  public:
    virtual void write(const std::string&) = 0;
    virtual void write(const std::vector<unsigned char>&) = 0;
  };
}


#endif
