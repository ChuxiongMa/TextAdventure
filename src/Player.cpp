#include "Player.hpp"
#include <math.h>
#include <memory>
#include "Weapon.hpp"
#include "Armor.hpp"

using namespace std;


textadventure::Player::Player(string username)
  : ICharacter("", Attributes(0)),
    username(username),
	experience(0),
	money(STARTING_MONEY),
	maxInventorySize(STARTING_INVENTORY_SIZE)
{
  attributes.health = STARTING_HEALTH;
  attributes.strength = STARTING_STAT_LEVELS;
  attributes.intelligence = STARTING_STAT_LEVELS;
  attributes.dexterity = STARTING_STAT_LEVELS;
  attributes.charisma = STARTING_STAT_LEVELS;
  attributes.level = 0;
}

string textadventure::Player::getUsername() {
  return username;
}

textadventure::Attributes textadventure::Player::getAllAttributes() {
  attributes.level = getLevel();
  return attributes;
}

int textadventure::Player::getExperience() const {
  return experience;
}
void textadventure::Player::modifyExperience(int delta) {
  experience += delta;
  clampZero(experience);
}
int textadventure::Player::getLevel() const {
  // TODO decide on some official formula
  // ex: 100^1.(level-1)
  const int BASE_EXPERIENCE_FACTOR = 100;
  int level = 0;
  int requiredExperience = 0;
  do {
    level++;
    double power = 1 + (double)((level - 1) / 10);
    requiredExperience = pow(BASE_EXPERIENCE_FACTOR, power);
  } while (experience >= requiredExperience);
  return level;
}

void textadventure::Player::setDescription(string newDescription) {
  description = newDescription;
}

int textadventure::Player::getMaxInventorySize() const {
  return maxInventorySize;
}
void textadventure::Player::modifyMaxInventorySize(int delta) {
  maxInventorySize += delta;
  clampZero(maxInventorySize);
}

int textadventure::Player::getUsedInventorySize() const {
  return inventory.size();
}

/*
 * WARNING: Player takes over ownership of ptr so it will be invalid after passing in.
 *          Consider change to shared_ptr if this is a big issue
 * return true if item successfully equipped
 * return false if inventory is full
 */
bool textadventure::Player::addToInventory(unique_ptr<Item> &newItem) {
  if (inventory.size() == maxInventorySize) {
    return false;
  }
  inventory.push_back(move(newItem));
  return true;
}

/*
 * return true if item successfully equipped
 * return false if item is not in inventory or not equippable or
 *  player doesn't meet requirements
 */
bool textadventure::Player::equipItem(const string &equippableItemKeyword) {
  // TODO consider switching to exceptions?
  // checks if in inventory
  for (int i = 0; i < inventory.size(); i++) {
    unique_ptr<Item> &u_pItem = inventory[i];
    Item *pItem = u_pItem.get();
    if (pItem->containsKeyword(equippableItemKeyword)) {
      // check item is actual equippable
      EquippableItem *pEquippableItem = dynamic_cast<EquippableItem *>(pItem);
      if (pEquippableItem == nullptr) {
        return false;
      }
      Attributes itemRequirements = pEquippableItem->getAttributeRequirements();
      if (!getAllAttributes().meetsRequirements(itemRequirements)) {
        return false;
      }
      equippedItems[pEquippableItem->getType()] = i;
      return true;
    }
  }
  return false;
}

vector<textadventure::EquippableItem *> textadventure::Player::getEquippedItems() const {
  vector<EquippableItem *> returnVector;
  for (pair<EquipType, int> equippedItemPair : equippedItems) {
    int equippedItemIndex = equippedItemPair.second;
    Item *equippedItem = inventory[equippedItemIndex].get();
    EquippableItem *equippableItem = dynamic_cast<EquippableItem *>(equippedItem);
    returnVector.push_back(equippableItem);
  }
  return returnVector;
}

textadventure::EquippableItem *textadventure::Player::getEquippedItem(textadventure::EquipType type) const {
  int index = equippedItems.at(type);
  return getEquippedItems()[index];
}

int textadventure::Player::getMoney() const {
	return money;
}
void textadventure::Player::modifyMoney(int delta) {
	money += delta;
	clampZero(money);
}

int textadventure::Player::getAttackValue() {
  Weapon *weapon = dynamic_cast<Weapon *>(getEquippedItem(textadventure::EquipType::WEAPON));
  if (weapon == nullptr) {
    return 0;
  }
  return weapon->getAttack();
}
int textadventure::Player::getDefenceValue() {
  int totalDefence = 0;
  for (auto item : equippedItems) {
    if (item.first != EquipType::WEAPON) {
      Armor *armor = dynamic_cast<Armor *>(getEquippedItems()[item.second]);
      totalDefence += armor->getDefence();
    }
  }
  return totalDefence;
}
