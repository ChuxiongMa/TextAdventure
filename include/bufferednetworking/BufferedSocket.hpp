#ifndef BUFFERED_SOCKET_H
#define BUFFERED_SOCKET_H

#include <vector>

#include <pipeable/IByteBufferAcceptor.hpp>
#include <bufferedprotocol/Bufferer.hpp>
#include <bufferedprotocol/Sender.hpp>
#include <networking/Socket.hpp>

using Bufferer = bufferedprotocol::Bufferer;
using Sender = bufferedprotocol::Sender;
using Socket = networking::Socket;
using PeernameResult = networking::PeernameResult;
using IByteBufferAcceptor = pipeable::IByteBufferAcceptor;
using ISender = pipeable::ISender;

namespace bufferednetworking {

  /**
   * This is an analogous counterpart to `Socket`. The difference is that any
   * incoming packet needs to be prepended with some number of bytes to
   * represent the size of the expected packet.
   */
  class BufferedSocket: public ISender, public IByteBufferAcceptor {
  public:
    BufferedSocket();
    BufferedSocket(Socket& socket);
    BufferedSocket(Socket* socket);

    /**
     * Dump the specified packet into the bufferer.
     *
     * @param packet the packet to dump into the buffer.
     */
    void write(const std::vector<unsigned char>& packet);

    /**
     * Dump the specified packet into the bufferer.
     *
     * @param packet the packet to dump into the buffer.
     */
    void write(const std::string& packet);

    /**
     * Sends the specified string to the remote host.
     *
     * @param payload the content to send.
     */
    void send(const std::string& packet);

    /**
     * Sends the specified buffer to the remote host.
     *
     * @param payload the content to send.
     */
    void send(const std::vector<unsigned char>& packet);

    /**
     * Gets the address of the remote host.
     */
    PeernameResult getPeername();

    /**
     * Registers the specified event handler for cases when a payload has been
     * fully buffered.
     *
     * @param callback the event handler to register.
     */
    void onRead(
      std::function<void(const std::vector<unsigned char>&)> callback
    );

    /**
     * Registers an event handler for the case when the socket has been closed.
     */
    void onClose(std::function<void (void)> callback);

  private:
    Bufferer bufferer;
    Sender sender;
    Socket* socket;
  };
}

#endif
