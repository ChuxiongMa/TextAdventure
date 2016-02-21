#include "Room.hpp"

textadventure::Door::Door(int destinationId, std::string direction, std::string description)
  : destinationId(destinationId),
    direction(direction),
    description(description)
{}

int textadventure::Door::getDestinationId() const {
  return destinationId;
}

std::string textadventure::Door::getDirection() const {
  return direction;
}

std::string textadventure::Door::getDescription() const {
  return description;
}

textadventure::Room::Room() {}

textadventure::Room::Room(int id, std::string description, std::string name) {
  this->id = id;
  this->description = description;
  this->name = name;
}
textadventure::Room::Room(int id, std::string description, std::string name, std::deque<Door> doors) {
  this->id = id;
  this->description = description;
  this->name = name;
  this->doors = doors;
}

int textadventure::Room::getId() const {
  return id;
}

std::string textadventure::Room::getDescription() const {
  return description;
}

std::string textadventure::Room::getName() const {
  return name;
}

void textadventure::Room::addDoor(Door addDoor) {
  doors.push_back(addDoor);
}

std::deque<textadventure::Door> textadventure::Room::getDoors() const {
  return doors;
}
