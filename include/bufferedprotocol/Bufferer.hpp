#ifndef BUFFERED_PROTOCOL_H
#define BUFFERED_PROTOCOL_H

#include <functional>
#include <vector>

#include <pipeable/IByteBufferAcceptor.hpp>

using BufferContainer = std::vector<unsigned char>;
using OnCompleteCallback = std::function<void (const BufferContainer&)>;

namespace bufferedprotocol {
  class Bufferer: public pipeable::IByteBufferAcceptor {
    int contentLength;
    int contentLengthState;
    BufferContainer buffered;
    std::vector<OnCompleteCallback> onCompletePacketHandlers;

    void appendInitialByte(unsigned char);
    void signalOnCompleteHandlers();
  public:
    void write(const BufferContainer&);
    void write(unsigned char);
    void write(const std::string&);
    void onCompletePacket(OnCompleteCallback);
    Bufferer();
  };
}

#endif
