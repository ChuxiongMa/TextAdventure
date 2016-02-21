#ifndef IPACKET_ACCEPTOR_H
#define IPACKET_ACCEPTOR_H

#include <vector>

class IPacketAcceptor {
public:
  void supplyPacket(const std::vector<unsigned char>& packet);
};

#endif
