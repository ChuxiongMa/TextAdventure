#ifndef USER_H
#define USER_H

#include <string>

namespace textadventure {
  class User {
    std::string username;
    std::string password;
  public:
    User();
    User(std::string, std::string);
    bool passwordMatches(std::string);
  };
}

#endif
