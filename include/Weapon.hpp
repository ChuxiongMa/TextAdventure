#ifndef WEAPON_H
#define WEAPON_H

#include "EquippableItem.hpp"

namespace textadventure {

class Weapon : public EquippableItem {
  public:
    Weapon(int id, vector<string> keywords, int attack);
    Weapon(int id, vector<string> keywords, string shortDesc, string longDesc,
        string description, int attack);
    Weapon(int id, vector<string> keywords, int attack, Attributes &requirements);
    Weapon(int id, vector<string> keywords, string shortDesc, string longDesc,
        string description, int attack, Attributes &requirements);
    virtual ~Weapon();
    int getAttack();
  private:
    Weapon();
    int attack;
  };

}

#endif
