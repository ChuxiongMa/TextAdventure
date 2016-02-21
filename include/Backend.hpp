#ifndef BACKEND_H
#define BACKEND_H

#include <string>
#include <GameState.hpp>

namespace textadventure {

  class Backend {
  public:
    virtual GameState getState() = 0;
    virtual void logIn(std::string, std::string) = 0;
    virtual void registerUser(std::string, std::string) = 0;
    virtual void handleAction(std::string) = 0;
  };
}

#endif
