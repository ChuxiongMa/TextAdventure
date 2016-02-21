#include <gtest/gtest.h>

#include <unistd.h>
#include "yamlinterface/YamlParser.hpp"

using namespace std;
using YamlParser = yaml::YamlParser;
using NPC = textadventure::NPC;
using Item = textadventure::Item;
using Room = textadventure::Room;

static string getMidgaardPath() {
  char cwd[200];
  getcwd(cwd, sizeof(cwd));
  string yamlPath(cwd);
  // replace test with midgaard
  yamlPath = yamlPath.substr(0, yamlPath.length() - 5);
  yamlPath = yamlPath + "bin/midgaard.yml";
  return yamlPath;
}

TEST(yamlParser, parseAreaName) {
  YamlParser midgaard = YamlParser(getMidgaardPath());
  EXPECT_EQ("Midgaard", midgaard.getAreaName());
}

TEST(yamlParser, parseNPC) {
  YamlParser midgaard = YamlParser(getMidgaardPath());

  vector<NPC> npcs = midgaard.getNPCs();
  NPC wizard = npcs[0];
  string expectedDesc = "The wizard looks old and senile, and yet he looks like a very powerful";
  expectedDesc += " wizard. He is equipped with fine clothing, and is wearing many fine";
  expectedDesc += " rings and bracelets.";
  EXPECT_EQ(expectedDesc, wizard.getDescription());
  EXPECT_EQ(3000, wizard.getId());
  EXPECT_TRUE(wizard.containsKeyword("wizard"));
  EXPECT_EQ("A wizard walks around behind the counter, talking to himself.", wizard.getLongDescription());
  EXPECT_EQ("the wizard", wizard.getShortDescription());
  EXPECT_EQ(55, npcs.size());
}

TEST(yamlParser, parseItem) {
  YamlParser midgaard = YamlParser(getMidgaardPath());

  vector<Item> items = midgaard.getItems();
  Item *scroll = nullptr;
  for (Item &item : items) {
     if (item.getId() == 3040) {
       scroll = &item;
       break;
     }
  }
  string expectedDesc = "The scroll has a magic formula drawn upon it:\n";
  expectedDesc += "     ???\n";
  expectedDesc += "    ?   ?\n";
  expectedDesc += "       ?\n";
  expectedDesc += "      ?\n";
  expectedDesc += "      ?\n";
  expectedDesc += "      *";
  EXPECT_EQ(expectedDesc, scroll->getDescription());
  EXPECT_EQ(3040, scroll->getId());
  EXPECT_TRUE(scroll->containsKeyword("scroll"));
  EXPECT_TRUE(scroll->containsKeyword("identify"));
  EXPECT_EQ("A scroll has carelessly been left here.", scroll->getLongDescription());
  EXPECT_EQ("a scroll of identify", scroll->getShortDescription());
  EXPECT_EQ(81, items.size());
}

TEST(yamlParser, parseRoom) {
  YamlParser midgaard = YamlParser(getMidgaardPath());

  vector<Room> rooms = midgaard.getRooms();
  Room temple = rooms[0];
  string expectedDesc = "   You are in the southern end of the temple hall in the Temple of Midgaard. ";
  expectedDesc += "The temple has been constructed from giant marble blocks, eternal in ";
  expectedDesc += "appearance, and most of the walls are covered by ancient wall paintings ";
  expectedDesc += "picturing Gods, Giants and peasants. ";
  expectedDesc += "   Large steps lead down through the grand temple gate, descending the huge ";
  expectedDesc += "mound upon which the temple is built and ends on the temple square below. ";
  expectedDesc += "   Equally large steps lead UP through a small door into the ENTRANCE to MUD ";
  expectedDesc += "SCHOOL.  (type 'up' to go to MUD SCHOOL.)  A small plaque is on this wall.";
  EXPECT_EQ(expectedDesc, temple.getDescription());
  EXPECT_EQ(3001, temple.getId());
  EXPECT_EQ("The Temple Of Midgaard", temple.getName());

  deque<textadventure::Door> templeDoors = temple.getDoors();
  EXPECT_EQ(3, templeDoors.size());
  EXPECT_EQ("At the northern end of the temple hall is a statue and a huge altar.", templeDoors[0].getDescription());
  EXPECT_EQ("north", templeDoors[0].getDirection());
  EXPECT_EQ(3054, templeDoors[0].getDestinationId());

  EXPECT_EQ("You see the temple square.", templeDoors[1].getDescription());
  EXPECT_EQ("south", templeDoors[1].getDirection());
  EXPECT_EQ(3005, templeDoors[1].getDestinationId());

  EXPECT_EQ("You see the entrance to Mud School.", templeDoors[2].getDescription());
  EXPECT_EQ("up", templeDoors[2].getDirection());
  EXPECT_EQ(3700, templeDoors[2].getDestinationId());

}
