#include <gtest/gtest.h>

#include "uvpp/GlobalLoop.hpp"
#include "uvpp/Loop.hpp"
#include "helpers/bcrypt.hpp"

using GlobalLoop = uvpp::GlobalLoop;
using Loop = uvpp::Loop;

TEST(BcryptTest, ItShouldEncryptAPasswordAndConfirm) {
  GlobalLoop::initializeLoop(Loop());

  std::string password = "Our super leet password";
  bool matches = false;

  textadventure::bcrypt::generateSalt(
    2,
    [&matches, password](std::string salt) {
      textadventure::bcrypt::performHash(
        password,
        salt,
        [&matches, password](std::string hash) {
          textadventure::bcrypt::verify(
            password,
            hash,
            [&matches](bool result) {
              matches = result;
            }
          );
        }
      );
    }
  );

  int result = GlobalLoop::runLoop();
  EXPECT_EQ(result, 0);
  EXPECT_EQ(true, matches);
}

TEST(BcryptTest, ItShouldEncryptAPasswordAndRejectBadOnes) {
  GlobalLoop::initializeLoop(Loop());

  std::string password = "Our super leet password";
  bool matches = true;

  textadventure::bcrypt::generateSalt(
    2,
    [&matches, password](std::string salt) {
      textadventure::bcrypt::performHash(
        password,
        salt,
        [&matches, password](std::string hash) {
          textadventure::bcrypt::verify(
            "some totally different password",
            hash,
            [&matches](bool result) {
              matches = result;
            }
          );
        }
      );
    }
  );

  int result = GlobalLoop::runLoop();
  EXPECT_EQ(false, matches);
  EXPECT_EQ(result, false);
}
