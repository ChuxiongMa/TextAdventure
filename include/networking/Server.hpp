#ifndef SERVER_H
#define SERVER_H

#include <uv.h>

#include <string>
#include <functional>
#include <vector>
#include <memory>

#include "Client.hpp"
#include "Socket.hpp"
#include "ServerStartException.hpp"

using string = std::string;

using SocketContainer = std::shared_ptr<networking::Socket>;
using OnConnectionCallback = std::function<void (SocketContainer)>;

namespace networking {
  struct ListenResult {
    ServerStartException error;
    bool failed;
    ListenResult();
    ListenResult(ServerStartException);
  };

  class Server {
    Socket socket;
    std::vector<OnConnectionCallback> connectionEventHandlers;
    std::vector<SocketContainer> clientSockets;
    std::vector<std::function<void (int)>> onErrorHandlers;
    uv_loop_t* loop;

    void clearClosedSockets();

    /**
     * An event listener intended for the libuv connection event.
     */
    static void libuvOnConnection(uv_stream_t *server, int status);
  public:
    /**
     * Opens a TCP port, awaiting connections from clients.
     */
    ListenResult listen(string, int);
    ListenResult listen(string, int, uv_loop_t*);

    /**
     * Adds the specified listener for events when a connection is made.
     */
    void onConnection(OnConnectionCallback);

    void onError(std::function<void (int)>);
  };
}

#endif
