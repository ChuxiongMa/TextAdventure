#include <bufferedprotocol/Bufferer.hpp>
#include <helpers/helperFunctions.hpp>

const int contentLengthContainerSize = 3;

using OnCompleteCallback = std::function<void (const BufferContainer&)>;

bufferedprotocol::Bufferer::Bufferer()
: contentLength(0)
, contentLengthState(0) {}

void bufferedprotocol::Bufferer::appendInitialByte(unsigned char b) {
  contentLength = b;
  contentLengthState = 1;
  buffered.clear();
}

void bufferedprotocol::Bufferer::signalOnCompleteHandlers() {
  for (auto handler : onCompletePacketHandlers) {
    handler(buffered);
  }
}

void bufferedprotocol::Bufferer::write(const std::string& packet) {
  write(helpers::stringToCharVector(packet));
}

void bufferedprotocol::Bufferer::write(const BufferContainer& packet) {
  for (auto byte : packet) {
      write(byte);
  }
}

void bufferedprotocol::Bufferer::write(unsigned char b) {
  if (contentLengthState == 0) {
    appendInitialByte(b);
  } else if (contentLengthState < contentLengthContainerSize) {
    contentLength = b | (contentLength << 1);
    contentLengthState++;
    contentLength = 0x00FFFFFF & contentLength;
  } else if (buffered.size() < contentLength) {
    buffered.push_back(b);
    if (buffered.size() == contentLength) {
      signalOnCompleteHandlers();
    }
  } else {
    appendInitialByte(b);
  }
}

void bufferedprotocol::Bufferer::onCompletePacket(OnCompleteCallback callback) {
  onCompletePacketHandlers.push_back(callback);
}
