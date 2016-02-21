#include <gtest/gtest.h>

#include "bufferedprotocol/Bufferer.hpp"

using OnCompleteCallback = std::function<void (const BufferContainer&)>;

TEST(BuffererTest, ItShouldBufferAPacket) {
  bufferedprotocol::Bufferer buf;
  bool packetCompleted = false;

  BufferContainer buffer = { 0x00, 0x00, 0x03, 0x05, 0x03, 0xFF };

  buf.onCompletePacket(
    [&packetCompleted, buffer](BufferContainer packet) {
      packetCompleted = true;
      for (int i = 0, size = packet.size(); i < size; i++) {
        EXPECT_EQ(packet[i], buffer[i + 3]);
      }
    }
  );

  buf.write(buffer);

  EXPECT_TRUE(packetCompleted);
}

TEST(BuffererTest, ItShouldBufferAPacketOneByteAtATime) {
  bufferedprotocol::Bufferer buf;
  bool packetCompleted = false;

  BufferContainer buffer = { 0x00, 0x00, 0x03, 0x05, 0x03, 0xFF };

  buf.onCompletePacket(
    [&packetCompleted, buffer](BufferContainer packet) {
      packetCompleted = true;

      for (int i = 0, size = packet.size(); i < size; i++) {
        EXPECT_EQ(packet[i], buffer[i + 3]);
      }
    }
  );

  for (int i = 0; i < buffer.size(); i++) {
    buf.write(buffer[i]);
  }

  EXPECT_TRUE(packetCompleted);
}

TEST(BuffererTest, ItShouldBufferChunksAtATime) {
  bufferedprotocol::Bufferer buf;
  bool packetCompleted = false;

  BufferContainer buffer = {
    0x00, 0x00, 0x03, 0x05, 0x03, 0xFF
  };

  buf.onCompletePacket(
    [&packetCompleted, buffer](BufferContainer packet) {
      packetCompleted = true;

      for (int i = 0, size = packet.size(); i < size; i++) {
        EXPECT_EQ(packet[i], buffer[i + 3]);
      }
    }
  );

  const int toBeInputed = 3;
  buf.write(
    std::vector<unsigned char>(buffer.begin(), buffer.begin() + toBeInputed)
  );
  for (int i = toBeInputed; i < buffer.size(); i++) {
    buf.write(buffer[i]);
  }

  EXPECT_TRUE(packetCompleted);
}

TEST(BuffererTest, ItShouldSignalTheEventOfMultiplePackets) {
  bufferedprotocol::Bufferer buf;
  int packetsCompleted = 0;

  BufferContainer buffer = {
    0x00, 0x00, 0x03, 0x05, 0x03, 0xFF,
    0x00, 0x00, 0x04, 0xDE, 0xAD, 0xC0, 0xDE
  };

  int lastPacketSize = 0;
  buf.onCompletePacket(
    [&lastPacketSize, &packetsCompleted, buffer](BufferContainer packet) {
      packetsCompleted++;

      for (int i = 0, size = packet.size(); i < size; i++) {
        EXPECT_EQ(packet[i], buffer[lastPacketSize + i + 3*packetsCompleted]);
      }

      lastPacketSize = packet.size();
    }
  );

  buf.write(buffer);

  EXPECT_EQ(packetsCompleted, 2);
}
