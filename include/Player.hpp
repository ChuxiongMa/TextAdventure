#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Item.hpp"
#include "EquippableItem.hpp"
#include "Attributes.hpp"
#include "ICharacter.hpp"

using namespace std;

static const int STARTING_STAT_LEVELS = 1;
static const int STARTING_HEALTH = 100;
static const int STARTING_INVENTORY_SIZE = 10;
static const int STARTING_MONEY = 0;

namespace textadventure {
  class Player : public ICharacter {
  public:
    Player(string username);

    Attributes getAllAttributes() override;

    string getUsername();

    int getExperience() const;
    void modifyExperience(int delta);
    int getLevel() const;

    void setDescription(string newDescription);
    int getMaxInventorySize() const;
    void modifyMaxInventorySize(int delta);
    int getUsedInventorySize() const;

    bool addToInventory(unique_ptr<Item> &newItem);
    bool equipItem(const string &equippableItemKeyword);
    vector<EquippableItem *> getEquippedItems() const;
    EquippableItem *getEquippedItem(EquipType type) const;

    int getMoney() const;
    void modifyMoney(int delta);

    virtual int getAttackValue() override;
    virtual int getDefenceValue() override;
  private:
    Player();
    string username;
    int experience;
    vector<unique_ptr<Item>> inventory;
    int maxInventorySize;
    // index to item location in inventory
    map<EquipType, int> equippedItems;
    int money;
  };
}

#endif
