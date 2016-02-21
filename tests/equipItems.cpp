#include <gtest/gtest.h>

#include <memory>
#include "Player.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "Item.hpp"

using Player = textadventure::Player;
using Item = textadventure::Item;
using Weapon = textadventure::Weapon;
using Armor = textadventure::Armor;
using EquippableItem = textadventure::EquippableItem;
using EquipType = textadventure::EquipType;
using Attributes = textadventure::Attributes;

TEST(equipItems, equipAllTypes) {
  Player testPlayer = Player("TestPlayer");

  unique_ptr<Item> gloves = unique_ptr<Item>(new Armor(0, vector<string>({"gloves"}), EquipType::HANDS, 4));
  unique_ptr<Item> helmet = unique_ptr<Item>(new Armor(1, vector<string>({"helmet"}), EquipType::HEAD, 1));
  unique_ptr<Item> boots = unique_ptr<Item>(new Armor(2, vector<string>({"boots"}), EquipType::FEET, 2));
  unique_ptr<Item> chestplate = unique_ptr<Item>(new Armor(3, vector<string>({"chestplate"}), EquipType::TORSO, 8));
  unique_ptr<Item> shorts = unique_ptr<Item>(new Armor(4, vector<string>({"shorts"}), EquipType::LEGS, 2));
  unique_ptr<Item> axe = unique_ptr<Item>(new Weapon(5, vector<string>({"axe"}), 5));

  EXPECT_TRUE(testPlayer.addToInventory(gloves));
  EXPECT_TRUE(testPlayer.addToInventory(helmet));
  EXPECT_TRUE(testPlayer.addToInventory(boots));
  EXPECT_TRUE(testPlayer.addToInventory(chestplate));
  EXPECT_TRUE(testPlayer.addToInventory(shorts));
  EXPECT_TRUE(testPlayer.addToInventory(axe));
  EXPECT_EQ(6, testPlayer.getUsedInventorySize());

  EXPECT_TRUE(testPlayer.equipItem("gloves"));
  EXPECT_TRUE(testPlayer.equipItem("helmet"));
  EXPECT_TRUE(testPlayer.equipItem("boots"));
  EXPECT_TRUE(testPlayer.equipItem("chestplate"));
  EXPECT_TRUE(testPlayer.equipItem("shorts"));
  EXPECT_TRUE(testPlayer.equipItem("axe"));
}

TEST(equipItems, swapEquipped) {
  Player testPlayer = Player("TestPlayer");
  unique_ptr<Item> gloves = unique_ptr<Item>(new Armor(0, vector<string>({"gloves"}), EquipType::HANDS, 4));
  unique_ptr<Item> supergloves = unique_ptr<Item>(new Armor(6, vector<string>({"supergloves"}), EquipType::HANDS, 40));
  EXPECT_TRUE(testPlayer.addToInventory(gloves));
  EXPECT_TRUE(testPlayer.addToInventory(supergloves));

  EXPECT_TRUE(testPlayer.equipItem("gloves"));
  auto equipped = testPlayer.getEquippedItems();
  EXPECT_TRUE(equipped[0]->containsKeyword("gloves"));
  EXPECT_TRUE(testPlayer.equipItem("supergloves"));
  equipped = testPlayer.getEquippedItems();
  EXPECT_TRUE(equipped[0]->containsKeyword("supergloves"));
}

TEST(equipItems, dontHaveItem) {
  Player testPlayer = Player("TestPlayer");
  unique_ptr<Item> gloves = unique_ptr<Item>(new Armor(0, vector<string>({"gloves"}), EquipType::HANDS, 4));
  EXPECT_FALSE(testPlayer.equipItem("gloves"));
}

TEST(equipItems, noRoom) {
  Player testPlayer = Player("TestPlayer");
  testPlayer.modifyMaxInventorySize(-1 * (testPlayer.getMaxInventorySize() - 1));
  unique_ptr<Item> gloves = unique_ptr<Item>(new Armor(0, vector<string>({"gloves"}), EquipType::HANDS, 4));
  unique_ptr<Item> axe = unique_ptr<Item>(new Weapon(5, vector<string>({"axe"}), 5));
  EXPECT_TRUE(testPlayer.addToInventory(gloves));
  EXPECT_FALSE(testPlayer.addToInventory(axe));
}

TEST(equipItems, failRequirements) {
  Player testPlayer = Player("TestPlayer");
  Attributes requirements = Attributes(5);
  unique_ptr<Item> gloves = unique_ptr<Item>(new Armor(0, vector<string>({"gloves"}), EquipType::HANDS, 4, requirements));
  EXPECT_TRUE(testPlayer.addToInventory(gloves));
  EXPECT_FALSE(testPlayer.equipItem("gloves"));
}

TEST(equipItems, accessEquipped) {
  Player testPlayer = Player("TestPlayer");
  unique_ptr<Item> gloves = unique_ptr<Item>(new Armor(0, vector<string>({"gloves"}), EquipType::HANDS, 4));
  unique_ptr<Item> axe = unique_ptr<Item>(new Weapon(5, vector<string>({"axe"}), 5));
  testPlayer.addToInventory(gloves);
  testPlayer.equipItem("gloves");
  testPlayer.addToInventory(axe);
  testPlayer.equipItem("axe");

  vector<EquippableItem *> items = testPlayer.getEquippedItems();
  EXPECT_EQ(2, items.size());
  EXPECT_TRUE(items[0]->containsKeyword("gloves"));
  EXPECT_TRUE(items[1]->containsKeyword("axe"));
}
