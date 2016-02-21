#include "Weapon.hpp"

textadventure::Weapon::Weapon(int id, vector<string> keywords, int attack)
  : Weapon(id, keywords, NO_DESCRIPTION, NO_DESCRIPTION, NO_DESCRIPTION, attack)
{}
textadventure::Weapon::Weapon(int id, vector<string> keywords, string shortDesc, string longDesc,
    string description, int attack)
  : EquippableItem(id, keywords, shortDesc, longDesc, description, EquipType::WEAPON),
    attack(attack)
{}

textadventure::Weapon::Weapon(int id, vector<string> keywords, int attack, Attributes &requirements)
  : Weapon(id, keywords, NO_DESCRIPTION, NO_DESCRIPTION, NO_DESCRIPTION, attack, requirements)
{}
textadventure::Weapon::Weapon(int id, vector<string> keywords, string shortDesc, string longDesc,
    string description, int attack, Attributes &requirements)
  : EquippableItem(id, keywords, shortDesc, longDesc, description, EquipType::WEAPON, requirements),
    attack(attack)
{}

textadventure::Weapon::~Weapon() {
}

int textadventure::Weapon::getAttack() {
  return attack;
}
