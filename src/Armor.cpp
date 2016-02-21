#include "Armor.hpp"


textadventure::Armor::Armor(int id, vector<string> keywords, EquipType type, int defence)
  : Armor(id, keywords, NO_DESCRIPTION, NO_DESCRIPTION, NO_DESCRIPTION, type, defence)
{}
textadventure::Armor::Armor(int id, vector<string> keywords, string shortDesc, string longDesc,
    string description, EquipType type, int defence)
  : EquippableItem(id, keywords, shortDesc, longDesc, description, type),
    defence(defence)
{}

textadventure::Armor::Armor(int id, vector<string> keywords, EquipType type, int defence, Attributes &requirements)
  : Armor(id, keywords, NO_DESCRIPTION, NO_DESCRIPTION, NO_DESCRIPTION, type, defence, requirements)
{}
textadventure::Armor::Armor(int id, vector<string> keywords, string shortDesc, string longDesc,
    string description, EquipType type, int defence, Attributes &requirements)
  : EquippableItem(id, keywords, shortDesc, longDesc, description, type, requirements),
    defence(defence)
{}

textadventure::Armor::~Armor() {
}

int textadventure::Armor::getDefence() {
  return defence;
}

