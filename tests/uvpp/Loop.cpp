#include <gtest/gtest.h>
#include <uv.h>

#include <uvpp/Loop.hpp>

using Loop = uvpp::Loop;

TEST(LoopTest, LoopMinDeferSkipTimeShouldBeGreaterThanZero) {
  EXPECT_GT(uvpp::Loop::minDeferSkipTime, 0);
}

TEST(LoopTest, ItShouldDefer) {
  Loop loop;
  loop.initialize();

  std::string str;

  loop.defer([&str]() {
    str = "Hello, World!";
  });

  int result = loop.runLoop();

  EXPECT_EQ(result, 0);
  EXPECT_EQ(str.compare("Hello, World!"), 0);
}

TEST(LoopTest, ItShouldTimeout) {
  Loop loop;
  loop.initialize();

  std::string str;

  loop.setTimeout(10, [&str]() {
    str = "Wikiwikiwaowikiwikiwaowao";
  });

  int result = loop.runLoop();

  EXPECT_EQ(result, 0);
  EXPECT_EQ(str.compare("Wikiwikiwaowikiwikiwaowao"), 0);
}

TEST(LoopTest, ItShouldDoThreadedWork) {
  Loop loop;
  loop.initialize();

  std::string str;

  int finalSum;
  int timesRun = 0;

  loop.doWork(
    [&timesRun]() {
      int sum = 0;
      for (int i = 0; i < 100; i++) {
        sum += i;
      }
      timesRun++;
      return new int(sum);
    },
    [&finalSum](void * value) {
      finalSum = *reinterpret_cast<int*>(value);
    }
  );

  int result = loop.runLoop();

  EXPECT_EQ(0, result);
  EXPECT_EQ(4950, finalSum);
  EXPECT_EQ(1, timesRun);
}
