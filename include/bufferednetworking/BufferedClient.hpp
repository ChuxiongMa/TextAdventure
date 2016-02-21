#ifndef BUFFERED_CLIENT_H
#define BUFFERED_CLIENT_H

#include <networking/Client.hpp>

#include "BufferedSocket.hpp"

using Client = networking::Client;
using BufferedSocket = bufferednetworking::BufferedSocket;

namespace bufferednetworking {
  class BufferedClient {
  public:
    BufferedClient();
    void connect(string, int);
    void connect(string, int, uv_loop_t*);
    void onConnect(std::function<void (void)>);
    void onError(std::function<void (int err)>);
    BufferedSocket* getSocket();
  private:
    BufferedSocket socket;
    Client client;
  };
}

#endif
