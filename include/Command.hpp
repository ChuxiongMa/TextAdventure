#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <memory>
#include "Player.hpp"

namespace textadventure {
  class Command {
  public:
    Command() : Command(nullptr) {};
    Command(std::shared_ptr<Player> player) {this->player = player;};
    virtual ~Command() {};
    virtual void execute() = 0;
  protected:
    std::shared_ptr<Player> player;
  private:
  };
}

#endif
