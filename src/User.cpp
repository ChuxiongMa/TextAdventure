#include <string>

#include "User.hpp"

using string = std::string;

textadventure::User::User() {}

textadventure::User::User(string username, string password) {
  this->username = username;
  this->password = password;
}

bool textadventure::User::passwordMatches(string password) {
  return this->password.compare(password) == 0;
}
