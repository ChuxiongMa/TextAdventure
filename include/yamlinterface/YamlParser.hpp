#ifndef YAMLPARSER_H
#define YAMLPARSER_H

#include <yaml-cpp/yaml.h>
#include <string>
#include <vector>
#include "NPC.hpp"
#include "Item.hpp"
#include "Room.hpp"

using namespace std;

namespace yaml {
  class YamlParser {
  public:
    YamlParser(string);
    string getAreaName();
    vector<textadventure::NPC> getNPCs() const;
    vector<textadventure::Item> getItems() const;
    vector<textadventure::Room> getRooms() const;
  private:
    YamlParser();
    vector<textadventure::NPC> parseNPCs();
    vector<textadventure::Item> parseItems();
    vector<textadventure::Room> parseRooms();
    string parseMultiLineString(YAML::Node, bool);
    vector<string> parseKeywords(YAML::Node);
    vector<textadventure::NPC> npcs;
    vector<textadventure::Item> items;
    vector<textadventure::Room> rooms;
    YAML::Node root;
  };


}


#endif
