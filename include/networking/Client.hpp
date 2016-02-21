#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include <iostream>

#include <uv.h>

#include "Socket.hpp"

using string = std::string;

namespace networking {
  class Client {
  public:
    void connect(string, int);
    void connect(string, int, uv_loop_t*);
    void onConnect(std::function<void (void)>);
    void onError(std::function<void (int err)>);
    Socket* getSocket();

  private:
    Socket socket;
    uv_connect_t connection;
    std::vector<std::function<void (void)>> onConnectListeners;
    std::vector<std::function<void (int)>> onErrorListeners;

    static void libuvOnConnect(uv_connect_t *req, int status);
  };
}

#endif
