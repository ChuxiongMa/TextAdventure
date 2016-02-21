#include <uv.h>

#include "networking/Socket.hpp"

const int ipv6StringSize = 39;

networking::PeernameResult::PeernameResult() {}
networking::PeernameResult::PeernameResult(int result) : result(result) {}
networking::PeernameResult::PeernameResult(
  int result,
  networking::Peername peername
)
  : result(result)
  , peername(peername) {}

networking::Socket::Socket() {
  hasClosed = false;
}

void networking::Socket::onRead(
  std::function<void (const std::vector<unsigned char>&)> callback
) {
  readEventHandlers.push_back(callback);
}

void networking::Socket::onClose(std::function<void (void)> callback) {
  closeHandlers.push_back(callback);
}

void onUVClose(uv_handle_t *handle) {
  auto socket = reinterpret_cast<networking::Socket*>(handle->data);
  socket->isClosed();
}

void networking::Socket::close() {
  uv_close(reinterpret_cast<uv_handle_t*>(&handle), onUVClose);
}

bool networking::Socket::isClosed() {
  if (!hasClosed) {
    hasClosed = !uv_is_active(reinterpret_cast<uv_handle_t*>(&handle));
    if (hasClosed) {
      for (auto handler : closeHandlers) {
        handler();
      }
    }
  }
  return hasClosed;
}

void networking::Socket::signalReadEventHandlers(
  const std::vector<unsigned char>& packet
) {
  for (auto handler : readEventHandlers) {
    handler(packet);
  }
}

void networking::Socket::signalErrorEventHandlers(int code) {
  for (auto handler : errorHandlers) {
    handler(code);
  }
}

void networking::Socket::libuvOnRead(
  uv_stream_t *stream,
  ssize_t nread,
  const uv_buf_t *buf
) {
  Socket *socket = reinterpret_cast<Socket *>(stream->data);

  if (nread < 0) {
    socket->signalErrorEventHandlers(nread);
    socket->isClosed();
    return;
  }

  std::vector<unsigned char> packet(buf->base, buf->base + nread);

  socket->signalReadEventHandlers(packet);
}

void networking::Socket::allocBuffer(
  uv_handle_t *handle,
  size_t suggested_size,
  uv_buf_t *buf
) {
  *buf = uv_buf_init((char*) malloc(suggested_size), suggested_size);
}

struct SockaddressInfo {
  struct sockaddr_storage addr;

  /**
   * Represents the result of getting peername. 0 means non-error, and non-zero
   * means error.
   */
  int peernameResult;

  SockaddressInfo();
  SockaddressInfo(struct sockaddr_storage addr, int result);
};

SockaddressInfo::SockaddressInfo() {}
SockaddressInfo::SockaddressInfo(struct sockaddr_storage addr, int result)
  : addr(addr)
  , peernameResult(result) {}

SockaddressInfo getSockaddrStorage(uv_tcp_t &handle) {
  struct sockaddr_storage addr;
  int len = sizeof(addr);
  int port;
  int addressResult = uv_tcp_getpeername(
    &handle,
    reinterpret_cast<struct sockaddr*>(&addr),
    &len
  );
  SockaddressInfo info(addr, addressResult);
  return info;
}

// TODO: code for getIpv6 and getIpv4 are exactly the same
networking::PeernameResult getIpv4(SockaddressInfo sockInfo) {
  char ipAddress[ipv6StringSize];
  networking::Peername addrInfo;

  auto sockAddress = reinterpret_cast<sockaddr_in*>(&sockInfo.addr);
  int err = uv_ip4_name(sockAddress, ipAddress, ipv6StringSize);
  if (err) {
    return networking::PeernameResult(err);
  }
  addrInfo.address = ipAddress;
  addrInfo.port = sockAddress->sin_port;
  addrInfo.addressType = networking::AddressType::ipv4;

  return networking::PeernameResult(err, addrInfo);
}

// TODO: code for getIpv6 and getIpv4 are exactly the same
networking::PeernameResult getIpv6(SockaddressInfo sockInfo) {
  char ipAddress[ipv6StringSize];
  networking::Peername addrInfo;

  auto sockAddress = reinterpret_cast<sockaddr_in6*>(&sockInfo.addr);
  int err = uv_ip6_name(sockAddress, ipAddress, ipv6StringSize);
  if (err) {
    return networking::PeernameResult(err);
  }
  addrInfo.address = ipAddress;
  addrInfo.port = sockAddress->sin6_port;
  addrInfo.addressType = networking::AddressType::ipv6;

  return networking::PeernameResult(err);
}

networking::PeernameResult getAddressInfo(SockaddressInfo sockInfo) {
  networking::PeernameResult peername;

  bool isIPv4 = sockInfo.addr.ss_family == AF_INET;

  if(isIPv4) {
    peername = getIpv4(sockInfo);
  } else {
    peername = getIpv6(sockInfo);
  }

  return peername;
}

networking::PeernameResult networking::Socket::getPeername() {
  SockaddressInfo sockInfo = getSockaddrStorage(this->handle);
  if (sockInfo.peernameResult == 0) {
    return getAddressInfo(sockInfo);
  }

  return networking::PeernameResult(sockInfo.peernameResult);
}

void networking::Socket::afterWrite(uv_write_t *request, int status) {}

void networking::Socket::write(const std::string& input) {
  send(input);
}

void networking::Socket::write(const std::vector<unsigned char>& input) {
  send(input);
}

void networking::Socket::send(const std::string& input) {
  uv_buf_t toSend[] = {
    { .base = (char *) input.c_str(), .len = input.size() }
  };
  int r = uv_write(
    &this->write_req,
    reinterpret_cast<uv_stream_t*>(&this->handle),
    toSend,
    1,
    networking::Socket::afterWrite
  );
  if (r) {
    signalErrorEventHandlers(r);
  }
}

void networking::Socket::send(const std::vector<unsigned char>& input) {
  write(std::string(input.begin(), input.end()));
}

void networking::Socket::pipe(pipeable::IByteBufferAcceptor& output) {
  onRead([&output](std::vector<unsigned char> packet) {
    output.write(packet);
  });
}
