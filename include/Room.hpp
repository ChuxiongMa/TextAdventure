#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <deque>

namespace textadventure {
class Door {
public:
    Door();
    Door(int, std::string, std::string);
    int getDestinationId() const;
    std::string getDirection() const;
    std::string getDescription() const;
private:
    int destinationId;
    std::string direction;
    std::string description;
};

class Room {
  public:
    Room();
    Room(int, std::string, std::string);
    Room(int, std::string, std::string, std::deque<Door>);
    int getId() const;
    std::string getDescription() const;
    std::string getName() const;
    void addDoor(Door);
    std::deque<Door> getDoors() const;
  private:
    int id;
    std::string description;
    std::string name;
    std::deque<Door> doors;
};
}

#endif
