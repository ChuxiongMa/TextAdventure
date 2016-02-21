#ifndef WORLD_H
#define WORLD_H

#include "Room.cpp"
#include "Player.hpp"
#include <unordered_map>
#include <memory>
namespace textadventure {

class World {
  public:
    std::shared_ptr<World> getInstance();
    void initializeWorld();
    void movePlayer(std::shared_ptr<Player>, int);
    void update();

  private:
    World();
    std::shared_ptr<World> instance;
    std::unordered_map<int, std::shared_ptr<Room>> rooms;
};
}

#endif
