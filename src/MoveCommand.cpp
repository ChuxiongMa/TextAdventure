/*
 * MoveCommand.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: andrew
 */

#include "MoveCommand.hpp"

namespace textadventure {

MoveCommand::MoveCommand(Door door) {
  this->door = door;
}

void MoveCommand::execute() {
  if (player != nullptr && door.getDestinationId() != -1) {
//    World& world = World.getInstance();
//    world.movePlayer(player, door.destinationId);

    // Move the player to the room pointed to by the door
  }
}

} /* namespace textadventure */
