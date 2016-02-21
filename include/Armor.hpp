#ifndef ARMOR_H
#define ARMOR_H

#include "EquippableItem.hpp"

namespace textadventure {

  class Armor : public EquippableItem {
  public:
    Armor(int id, vector<string> keywords, EquipType type, int defence);
    Armor(int id, vector<string> keywords, string shortDesc, string longDesc,
        string description, EquipType type, int defence);
    Armor(int id, vector<string> keywords, EquipType type, int defence, Attributes &requirements);
    Armor(int id, vector<string> keywords, string shortDesc, string longDesc,
        string description, EquipType type, int defence, Attributes &requirements);
    virtual ~Armor();
    int getDefence();
  private:
    Armor();
    int defence;
  };

}

#endif
