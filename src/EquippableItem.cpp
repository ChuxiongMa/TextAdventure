#include "EquippableItem.hpp"
#include "Player.hpp"


textadventure::EquippableItem::EquippableItem(int id, vector<string> keywords, string shortDesc, string longDesc,
    string description, EquipType type)
  : EquippableItem(id, keywords, shortDesc, longDesc, description, type, textadventure::Attributes(0))
{}

textadventure::EquippableItem::EquippableItem(int id, vector<string> keywords, string shortDesc, string longDesc,
    string description, EquipType type, textadventure::Attributes requirements)
  : textadventure::Item(id, keywords, shortDesc, longDesc, description),
    type(type),
    requirements(requirements)
{}

textadventure::EquippableItem::~EquippableItem() {
}

textadventure::EquipType textadventure::EquippableItem::getType() const {
  return type;
}

textadventure::Attributes textadventure::EquippableItem::getAttributeRequirements() const {
  return requirements;
}

