#include <gtest/gtest.h>

#include "Combat.hpp"
#include "ICharacter.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include <vector>
#include <string>
#include <memory>
#include "Weapon.hpp"
#include "Item.hpp"

#include <iostream>

using ICharacter = textadventure::ICharacter;
using Combat = textadventure::Combat;
using Player = textadventure::Player;
using NPC = textadventure::NPC;
using Weapon = textadventure::Weapon;
using Item = textadventure::Item;


TEST(combat, startNPCBattle) {
  Player *player = new Player("Bryan");
  player->setIsOptedInForBattles(true);
  const char* keyword[] = {"a"};
  std::vector<std::string> keywords(keyword, keyword + 1);
  NPC *npc = new NPC(1, keywords, "a", "a", "a", 10, 10);

  bool battleCreated = Combat::getInstance().startBattle(player, npc);

  EXPECT_TRUE(battleCreated);
  EXPECT_TRUE(Combat::getInstance().endBattle(*player));
  delete player;
  delete npc;
}
TEST(combat, startPlayerBattle) {
  Player *player = new Player("A");
  player->setIsOptedInForBattles(true);
  Player *player2 = new Player("B");
  player2->setIsOptedInForBattles(true);

  bool battleCreated = Combat::getInstance().startBattle(player, player2);

  EXPECT_TRUE(battleCreated);
  EXPECT_TRUE(Combat::getInstance().endBattle(*player));
  delete player;
  delete player2;
}

TEST(combat, playerNotOptedIn) {
  Player *player = new Player("Bryan");
  const char* keyword[] = {"a"};
  std::vector<std::string> keywords(keyword, keyword + 1);
  NPC *npc = new NPC(1, keywords, "a", "a", "a", 10, 10);

  bool battleCreated = Combat::getInstance().startBattle(player, npc);

  EXPECT_FALSE(battleCreated);
  EXPECT_FALSE(Combat::getInstance().endBattle(*player));
  delete player;
  delete npc;
}

TEST(combat, notFightableNPC) {
  Player *player = new Player("Bryan");
  player->setIsOptedInForBattles(true);
  const char* keyword[] = {"a"};
  std::vector<std::string> keywords(keyword, keyword + 1);
  NPC *npc = new NPC(1, keywords, "a", "a", "a");

  bool battleCreated = Combat::getInstance().startBattle(player, npc);

  EXPECT_FALSE(battleCreated);
  EXPECT_FALSE(Combat::getInstance().endBattle(*player));
  delete player;
  delete npc;
}
TEST(combat, alreadyInBattle) {
  Player *player = new Player("Bryan");
  player->setIsOptedInForBattles(true);
  const char* keyword[] = {"a"};
  std::vector<std::string> keywords(keyword, keyword + 1);
  NPC *npc = new NPC(1, keywords, "a", "a", "a", 10, 10);

  bool battleCreated = Combat::getInstance().startBattle(player, npc);


  Player *player2 = new Player("A");
  player->setIsOptedInForBattles(true);
  bool battleCreated2 = Combat::getInstance().startBattle(player, player2);

  EXPECT_TRUE(battleCreated);
  EXPECT_TRUE(Combat::getInstance().endBattle(*player));
  EXPECT_FALSE(battleCreated2);
  EXPECT_FALSE(Combat::getInstance().endBattle(*player2));
  delete player;
  delete npc;
  delete player2;
}

TEST(combat, basicAttack) {
  Player *player = new Player("Bryan");
  player->setIsOptedInForBattles(true);
  player->modifyDexterity(10);

  const char* keyword[] = {"a"};
  std::vector<std::string> keywords(keyword, keyword + 1);
  NPC *npc = new NPC(1, keywords, "a", "a", "a", 10, 10);
  npc->modifyDexterity(1);

  EXPECT_TRUE(Combat::getInstance().startBattle(player, npc));
  int npcStartingHealth = npc->getHealth();

  unique_ptr<Item> axe = unique_ptr<Item>(new Weapon(1, vector<std::string>({"axe"}), 500));
  EXPECT_TRUE(player->addToInventory(axe));
  EXPECT_TRUE(player->equipItem("axe"));

  EXPECT_TRUE(Combat::getInstance().performAttack(*player));
  EXPECT_TRUE(npc->getHealth() < npcStartingHealth);

  if (npc->getHealth() > 0) {
    EXPECT_TRUE(Combat::getInstance().endBattle(*player));
  }
  delete player;
  delete npc;
}

TEST(combat, attackNotDuringTurn) {
  Player *player = new Player("A");
  player->setIsOptedInForBattles(true);
  player->modifyDexterity(2);

  Player *player2 = new Player("B");
  player2->setIsOptedInForBattles(true);
  player2->modifyDexterity(1);

  EXPECT_TRUE(Combat::getInstance().startBattle(player, player2));

  EXPECT_FALSE(Combat::getInstance().performAttack(*player2));

  EXPECT_TRUE(Combat::getInstance().endBattle(*player2));
  delete player;
  delete player2;
}

TEST(combat, run) {
  Player *player = new Player("A");
  player->setIsOptedInForBattles(true);
  player->modifyDexterity(-1);
  player->modifyIntelligence(-1);

  Player *player2 = new Player("B");
  player2->setIsOptedInForBattles(true);
  player2->modifyDexterity(10);
  player2->modifyIntelligence(3);

  EXPECT_TRUE(Combat::getInstance().startBattle(player, player2));

  EXPECT_TRUE(Combat::getInstance().attemptRun(*player2));

  EXPECT_FALSE(Combat::getInstance().endBattle(*player2));
  delete player;
  delete player2;
}
