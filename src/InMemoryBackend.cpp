#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

#include "InMemoryBackend.hpp"
#include "GameState.hpp"
#include "User.hpp"
#include "Room.hpp"

using namespace std;

textadventure::InMemoryBackend::InMemoryBackend() {
  /*vector<textadventure::Room> tempRooms;
  tempRooms.push_back(
    textadventure::Room(
      1,
      "This is a mystical place",
      textadventure::RoomDoors(-1, 2, -1, -1)
    )
  );
  tempRooms.push_back(
    textadventure::Room(
      2,
      "This is yet another mystical place",
      textadventure::RoomDoors(-1, -1, 1, -1)
    )
  );

  // unordered_map<int, textadventure::Room> *rooms = &this->rooms;
  //
  for (auto room : tempRooms) {
    this->rooms[room.getId()] = room;
  }

  this->state.room = this->rooms[1];*/
}

textadventure::GameState textadventure::InMemoryBackend::getState() {
  return this->state;
}

void textadventure::InMemoryBackend::logIn(string username, string password) {
  auto iterator = this->users.find(username);
  if (iterator == this->users.end()) {
    this->state.error = textadventure::FAILED_LOGIN;
    return;
  }
  auto user = this->users[username];
  if (!user.passwordMatches(password)) {
    this->state.error = textadventure::FAILED_LOGIN;
    return;
  }
  this->state.loggedIn = true;
}

void textadventure::InMemoryBackend::registerUser(string username, string password) {
  auto iterator = this->users.find(username);
  if (iterator != this->users.end()) {
    this->state.error = textadventure::USER_EXISTS;
    return;
  }
  User user(username, password);
  this->users[username] = user;
}

void textadventure::InMemoryBackend::handleChangeRoom(string direction) {
  cout << direction << endl;
/*
  if (direction.compare("north") == 0) {
    if (this->state.room.getRoomDoors().north == -1) {
      this->state.message = "You can't leave by that door";
    } else {
      this->state.room = this->rooms[this->state.room.getRoomDoors().north];
    }
  } else if (direction.compare("east") == 0) {
    if (this->state.room.getRoomDoors().east == -1) {
      this->state.message = "You can't leave by that door";
    } else {
      this->state.room = this->rooms[this->state.room.getRoomDoors().east];
    }
  } else if (direction.compare("west") == 0) {
    if (this->state.room.getRoomDoors().west == -1) {
      this->state.message = "You can't leave by that door";
    } else {
      this->state.room = this->rooms[this->state.room.getRoomDoors().west];
    }
  } else if (direction.compare("south") == 0) {
    if (this->state.room.getRoomDoors().south == -1) {
      this->state.message = "You can't leave by that door";
    } else {
      this->state.room = this->rooms[this->state.room.getRoomDoors().south];
    }
  } else {
    this->state.message = "Invalid door";
  }
  */
}

void textadventure::InMemoryBackend::handleAction(string action) {
  this->state.firstRun = false;
  this->state.message = "";

  vector<string> strings;
  boost::split(strings, action, boost::is_any_of(" "));

  if (strings[0].compare("go") == 0) {
    if (strings.size() < 2) {
      this->state.message = "Invalid door";
    } else {
      this->handleChangeRoom(strings[1]);
    }
  }
}
