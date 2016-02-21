#ifndef ISENDER_H
#define ISENDER_H

#include <string>
#include <vector>

namespace pipeable {
  class ISender {
  public:
    /**
     * Sends the specified string to the remote host.
     *
     * @param payload the content to send.
     */
    virtual void send(const std::string& packet) = 0;

    /**
     * Sends the specified buffer to the remote host.
     *
     * @param payload the content to send.
     */
    virtual void send(const std::vector<unsigned char>& packet) = 0;
  };
}

#endif
