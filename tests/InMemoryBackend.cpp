#include <gtest/gtest.h>
#include <string>

#include "InMemoryBackend.hpp"

using string = std::string;
using InMemoryBackend = textadventure::InMemoryBackend;

TEST(InMemoryBackendTest, ItShouldRegisterANewUser) {
  const string username = "mike";
  const string password = "Hello, World!";

  InMemoryBackend backend;
  backend.registerUser("mike", "Hello, World!");
  auto state = backend.getState();
  EXPECT_EQ(state.loggedIn, false);
  backend.logIn("mike", "Hello, World!");
  state = backend.getState();
  EXPECT_EQ(state.loggedIn, true);
}
