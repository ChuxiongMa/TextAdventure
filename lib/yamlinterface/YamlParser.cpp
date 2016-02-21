#include "yamlinterface/YamlParser.hpp"

#include <iostream>
#include <assert.h>
#include <algorithm>

using namespace std;

static string AREA_KEY = "AREA";
static string AREA_NAME_KEY = "name";

static string NPC_KEY = "NPCS";
static string NPC_DESCRIPTION_KEY = "description";

static string ITEM_EXTRA_KEY = "extra";
static string ITEM_DESCRIPTION_KEY = "desc";

static string ROOM_KEY = "ROOMS";
static string ROOM_NAME_KEY = "name";
static string ROOM_DESCRIPTION_KEY = "desc";
static string ROOM_DOORS_KEY = "doors";
static string ROOM_DOORS_DESCRIPTION_KEY = "desc";
static string ROOM_DOORS_DIRECTION_KEY = "dir";
static string ROOM_DOORS_TOID_KEY = "to";


static string ID_KEY = "id";
static string KEYWORDS_KEY = "keywords";
static string LONGDESC_KEY = "longdesc";
static string SHORTDESC_KEY = "shortdesc";

static string ITEM_KEY = "OBJECTS";

yaml::YamlParser::YamlParser(string filePath)
  : root(YAML::LoadFile(filePath))
{
  npcs = parseNPCs();
  items = parseItems();
  rooms = parseRooms();
}

string yaml::YamlParser::getAreaName() {
  return root[AREA_KEY][AREA_NAME_KEY].as<string>();
}

vector<textadventure::NPC> yaml::YamlParser::getNPCs() const {
  return npcs;
}

vector<textadventure::NPC> yaml::YamlParser::parseNPCs() {
  vector<textadventure::NPC> npcs;
  YAML::Node npcsRoot = root[NPC_KEY];

  for (YAML::Node npc : npcsRoot) {
    int id = npc[ID_KEY].as<int>();
    vector<string> keywords = parseKeywords(npc);
    string description = parseMultiLineString(npc[NPC_DESCRIPTION_KEY], false);
    string longDesc = parseMultiLineString(npc[LONGDESC_KEY], false);
    string shortDesc = npc[SHORTDESC_KEY].as<string>();

    npcs.push_back(textadventure::NPC(id, keywords, shortDesc, longDesc, description));
  }
  return npcs;
}

vector<textadventure::Item> yaml::YamlParser::getItems() const {
  return items;
}

vector<textadventure::Item> yaml::YamlParser::parseItems() {
  vector<textadventure::Item> items;
  YAML::Node itemsRoot = root[ITEM_KEY];
  for (YAML::Node item : itemsRoot) {
    int id = item[ID_KEY].as<int>();
    vector<string> keywords = parseKeywords(item);
    string longDesc = parseMultiLineString(item[LONGDESC_KEY], false);
    string shortDesc = item[SHORTDESC_KEY].as<string>();

    string description = textadventure::Item::NO_DESCRIPTION;
    YAML::Node extras = item[ITEM_EXTRA_KEY];
    assert(extras.IsSequence());
    for (YAML::Node extra : extras) {
      if (extra[ITEM_DESCRIPTION_KEY]) {
        description = parseMultiLineString(extra[ITEM_DESCRIPTION_KEY], true);
      }
    }
    items.push_back(textadventure::Item(id, keywords, shortDesc, longDesc, description));
  }
  return items;
}

vector<textadventure::Room> yaml::YamlParser::getRooms() const {
  return rooms;
}

vector<textadventure::Room> yaml::YamlParser::parseRooms() {
  vector<textadventure::Room> rooms;
  YAML::Node roomsRoot = root[ROOM_KEY];
  for (YAML::Node room : roomsRoot) {
    string roomDescription = parseMultiLineString(room[ROOM_DESCRIPTION_KEY], false);
    string name = room[ROOM_NAME_KEY].as<string>();
    int id = room[ID_KEY].as<int>();

    textadventure::Room parsedRoom = textadventure::Room(id, roomDescription, name);
    for (YAML::Node door : room[ROOM_DOORS_KEY]) {
      string doorDescription = parseMultiLineString(door[ROOM_DOORS_DESCRIPTION_KEY], false);
      string direction = door[ROOM_DOORS_DIRECTION_KEY].as<string>();
      int toId = door[ROOM_DOORS_TOID_KEY].as<int>();
      parsedRoom.addDoor(textadventure::Door(toId, direction, doorDescription));
    }
    rooms.push_back(parsedRoom);
  }
  return rooms;
}



string yaml::YamlParser::parseMultiLineString(YAML::Node sequenceNode, bool keepNewLines) {
  string separator = " ";
  if (keepNewLines) {
    separator = "\n";
  }
  string completeString = "";
  assert(sequenceNode.IsSequence());
  for (YAML::Node line : sequenceNode) {
    completeString += line.as<string>() + separator;
  }
  // remove last space
  completeString = completeString.substr(0, completeString.length() - 1);
  return completeString;
}

vector<string> yaml::YamlParser::parseKeywords(YAML::Node node) {
  vector<string> keywords;
  YAML::Node keywordsNode = node[KEYWORDS_KEY];
  keywords.resize(keywordsNode.size());
  assert(keywordsNode.IsSequence());
  std::transform(keywordsNode.begin(), keywordsNode.end(), keywords.begin(),
      [](YAML::Node n) -> string { return n.as<string>(); });
  return keywords;
}
