#include <gtest/gtest.h>

#include <helpers/helperFunctions.hpp>
#include <bufferedprotocol/Sender.hpp>

using Packet = std::vector<unsigned char>;
using OnReadHandler = std::function<void (const Packet& packet)>;

class FakeAcceptor: public pipeable::IByteBufferAcceptor {
  std::vector<OnReadHandler> onReadHandlers;
public:
  void onRead(OnReadHandler callback) {
    onReadHandlers.push_back(callback);
  }
  void write(const Packet& packet) {
    for (auto handler : onReadHandlers) {
      handler(packet);
    }
  }
  void write(const std::string& packet) {
    write(helpers::stringToCharVector(packet));
  }
};

TEST(SenderTest, ItShouldBeAbleToFormatAPacketWithASize) {
  FakeAcceptor acceptor;

  bool packetRead = false;

  acceptor.onRead([&packetRead](const Packet& packet) {
    packetRead = true;
    int size =
      (
        packet[0] |
        (packet[1] << 8) |
        (packet[2] << 16)
      ) & 0x00FFFFFF;

    EXPECT_EQ(5, size);
  });

  bufferedprotocol::Sender sender(acceptor);

  sender.write(Packet({1, 2, 3, 4, 5}));

  EXPECT_TRUE(packetRead);
}

TEST(SenderTest, ItShouldBeAbleToAcceptStrings) {
  FakeAcceptor acceptor;

  bool packetRead = false;
  std::string str = "Hello, World!";

  acceptor.onRead([&packetRead, str](const Packet& packet) {
    packetRead = true;
    int size =
      (
        packet[0] |
        (packet[1] << 8) |
        (packet[2] << 16)
      ) & 0x00FFFFFF;

    EXPECT_EQ(str.size(), size);

    std::string extractedStr(packet.begin() + 3, packet.end());
    EXPECT_EQ(str.compare(extractedStr), 0);
  });

  bufferedprotocol::Sender sender(acceptor);

  sender.write("Hello, World!");

  EXPECT_TRUE(packetRead);
}
