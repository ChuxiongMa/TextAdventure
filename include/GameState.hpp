#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <string>

#include "Room.hpp"

using namespace std;

namespace textadventure {
  struct GameState {
    string error;
    bool loggedIn;
    bool firstRun;
    Room room;
    std::string message;
    GameState();
  };
}

#endif
