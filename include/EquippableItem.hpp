#ifndef EQUIPPABLEITEM_H
#define EQUIPPABLEITEM_H

#include "Item.hpp"
#include "Attributes.hpp"
#include <vector>

namespace textadventure {
  enum EquipType {
    HEAD,
    TORSO,
    LEGS,
    HANDS,
    FEET,
    WEAPON
  };

  class EquippableItem : public Item {
  public:
    virtual ~EquippableItem();
    EquipType getType() const;
    Attributes getAttributeRequirements() const;
  private:
    EquippableItem();
    EquipType type;
    Attributes requirements;
  protected:
    EquippableItem(int id, vector<string> keywords, string shortDesc, string longDesc,
        string description, EquipType type);
    EquippableItem(int id, vector<string> keywords, string shortDesc, string longDesc,
        string description, EquipType type, Attributes requirements);
  };

}

#endif
