#ifndef BUFFERED_SERVER_H
#define BUFFERED_SERVER_H

#include <map>
#include <functional>
#include <memory>
#include <string>

#include <uv.h>
#include <networking/Server.hpp>

#include "BufferedSocket.hpp"

using Server = networking::Server;
using Socket = networking::Socket;
using ListenResult = networking::ListenResult;

namespace bufferednetworking {
  class BufferedServer {
    Server server;
    std::map<std::shared_ptr<Socket>, BufferedSocket> proxies;
  public:
    ListenResult listen(std::string host, int port);
    ListenResult listen(std::string host, int port, uv_loop_t* loop);
    void onConnection(std::function<void (BufferedSocket&)> callback);
  };
}

#endif
