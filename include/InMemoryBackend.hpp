#ifndef INMEMORYBACKEND_H
#define INMEMORYBACKEND_H

#include <string>
#include <vector>
#include <unordered_map>

#include "GameState.hpp"
#include "User.hpp"
#include "Backend.hpp"
#include "Room.hpp"

using string = std::string;

namespace textadventure {
  const string USER_EXISTS = "USER_EXISTS";
  const string FAILED_LOGIN = "FAILED_LOGIN";

  class InMemoryBackend: public Backend {
    std::unordered_map<std::string, User> users;
    std::unordered_map<int, Room> rooms;
    GameState state;

    void handleChangeRoom(std::string);
  public:
    InMemoryBackend();
    GameState getState();
    void logIn(string, string);
    void registerUser(string, string);
    void handleAction(string);
  };
}

#endif
