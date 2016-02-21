#include <GameState.hpp>
#include <iostream>

using namespace std;

textadventure::GameState::GameState() {
  this->loggedIn = false;
  this->firstRun = true;
}
