#ifndef SOCKET_H
#define SOCKET_H

#include <vector>
#include <iostream>
#include <string>
#include <functional>

#include <uv.h>

#include <pipeable/IByteBufferAcceptor.hpp>
#include <pipeable/ISender.hpp>

using IByteBufferAcceptor = pipeable::IByteBufferAcceptor;
using ISender = pipeable::ISender;

namespace networking {
  class Server;
  class Client;

  enum AddressType { ipv4, ipv6 };

  struct Peername {
    std::string address;
    AddressType addressType;
    int port;
  };

  struct PeernameResult {
    Peername peername;
    int result;
    PeernameResult();
    PeernameResult(int result);
    PeernameResult(int result, Peername peername);
  };

  class Socket: public ISender, public IByteBufferAcceptor {
    friend class Server;
    friend class Client;

  public:
    Socket();

    /**
     * Attach an event listener for when the socket gets a payload.
     *
     * @param callback is the event listener.
     */
    void onRead(std::function<void (const std::vector<unsigned char>&)>);

    /**
     * Attach an event listener for when an error occures.
     *
     * @param callback is the event listener.
     */
    void onError(std::function<void (int)>);

    /**
     * Attach an event listener for when the socket is closed.
     *
     * @param callback is the event listener.
     */
    void onClose(std::function<void ()>);

    /**
     * Closes the socket.
     */
    void close();

    /**
     * Returns true if the socket is closed; false otherwise.
     *
     * @returns the state of the socket.
     */
    bool isClosed();

    /**
     * Gets the port and IP address of the remote host.
     */
    PeernameResult getPeername();

    /**
     * Sends the specified string to the remote host.
     *
     * @param payload the content to send.
     */
    void write(const std::string&);

    /**
     * Sends the specified string to the remote host.
     *
     * @param payload the content to send.
     */
    void write(const std::vector<unsigned char>&);

    /**
     * Sends the specified string to the remote host.
     *
     * @param payload the content to send.
     */
    void send(const std::string&);

    /**
     * Sends the specified buffer to the remote host.
     *
     * @param payload the content to send.
     */
    void send(const std::vector<unsigned char>&);

    /**
     * Pipes all incoming payloads into the byte buffer acceptor
     *
     * @param acceptor the byte buffer acceptor to pipe the payloads into.
     */
    void pipe(pipeable::IByteBufferAcceptor&);

  private:

    uv_tcp_t handle;
    uv_write_t write_req;
    std::vector<std::function<void (const std::vector<unsigned char>&)>>
      readEventHandlers;
    std::vector<std::function<void (int)>> errorHandlers;
    std::vector<std::function<void (void)>> closeHandlers;
    bool hasClosed;

    void signalReadEventHandlers(const std::vector<unsigned char>&);
    void signalErrorEventHandlers(int code);

    static void allocBuffer(uv_handle_t*, size_t, uv_buf_t*);
    static void libuvOnRead(uv_stream_t*, ssize_t, const uv_buf_t*);
    static void afterWrite(uv_write_t *request, int status);
  };
}

#endif
