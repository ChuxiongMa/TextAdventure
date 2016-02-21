#include "World.hpp"
#include "Room.hpp"
#include <iostream>
#include <deque>

namespace textadventure {
void World::initializeWorld() {
//  std::deque<textadventure::Door> doors;
//  doors.push_back(Door(2, "east"));
//  rooms.emplace(1, std::make_shared<Room>(1, "This is a mystical place", doors));
//  doors.clear();
//  doors.push_back(Door(1, "west"));
//  rooms.emplace(2, std::make_shared<Room>(2, "This is yet another mystical place", doors));
}

void World::movePlayer(std::shared_ptr<Player> player, int destRoom) {

}

} /* namespace textadventure */
