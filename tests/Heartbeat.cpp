#include <gtest/gtest.h>
#include <Heartbeat.hpp>
#include <IUpdateable.hpp>
#include <uvpp/GlobalLoop.hpp>

/**
 * Just pretend that this is our game.
 */
class FakeGame: public textadventure::IUpdateable {
public:

  FakeGame(): count(0) {}

  void update() override {
    // In our actual game, the logic should involve more than just incrementing
    // a counter. :)

    count++;
  }

  bool hasStopped() override {
    return count == maxCount;
  }

  /////////////////////////////////////////////////////////////////////////////

  /**
   * Gets the number of times that the game's update code has been called.
   */
  int getCount() {
    return count;
  }

  static const int maxCount;
private:
  int count;
};

const int FakeGame::maxCount = 10;

///////////////////////////////////////////////////////////////////////////////

TEST(Heartbeat, ItShouldStartRunAndStop) {
  uvpp::GlobalLoop::initializeLoop();

  FakeGame updater;

  // For unit tests, we don't care about a delay. But otherwise, in the real
  // thing, we are expected to have a delay greater than 0.
  int timeout = 0;

  textadventure::Heartbeat heartbeat(updater, timeout);

  // And let the game begin.
  heartbeat.start();

  int result = uvpp::GlobalLoop::runLoop();

  EXPECT_EQ(0, result);
  EXPECT_EQ(updater.getCount(), FakeGame::maxCount);
}
