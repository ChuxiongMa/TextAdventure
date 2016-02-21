#include <memory>
#include <iostream>

#include <gtest/gtest.h>
#include <uv.h>

#include <uvpp/GlobalLoop.hpp>

using Loop = uvpp::Loop;
using GlobalLoop = uvpp::GlobalLoop;

TEST(GlobalLoopTest, ItShouldDefer) {
  GlobalLoop::initializeLoop(Loop());

  std::string str;

  GlobalLoop::defer([&str]() {
    str = "Hello, World!";
  });

  int result = GlobalLoop::runLoop();

  EXPECT_EQ(result, 0);
  EXPECT_EQ(str.compare("Hello, World!"), 0);
}

TEST(GlobalLoopTest, ItShouldTimeout) {
  GlobalLoop::initializeLoop(Loop());

  std::string str;

  GlobalLoop::setTimeout(10, [&str]() {
    str = "Wikiwikiwaowikiwikiwaowao";
  });

  int result = GlobalLoop::runLoop();

  EXPECT_EQ(result, 0);
  EXPECT_EQ(str.compare("Wikiwikiwaowikiwikiwaowao"), 0);
}

TEST(GlobalLoopTest, ItShouldDoThreadedWork) {
  GlobalLoop::initializeLoop(Loop());

  int finalSum;
  int timesRun = 0;

  GlobalLoop::doWork(
    [&timesRun]() {
      int sum = 0;
      for (int i = 0; i < 100; i++) {
        sum += i;
      }
      timesRun++;
      return new int(sum);
    },
    [&finalSum](void* value) {
      finalSum = *reinterpret_cast<int*>(value);
    }
  );

  int result = GlobalLoop::runLoop();

  EXPECT_EQ(0, result);
  EXPECT_EQ(4950, finalSum);
  EXPECT_EQ(1, timesRun);
}
