#ifndef ICHARACTER_H
#define ICHARACTER_H

#include "Attributes.hpp"
#include <string>

using string = std::string;

namespace textadventure {
	class ICharacter {
	public:
		string getDescription() const;
    virtual Attributes getAllAttributes();
    int getHealth() const;
    int getStrength() const;
    int getIntelligence() const;
    int getDexterity() const;
    int getCharisma() const;
    void modifyHealth(int delta);
    void modifyStrength(int delta);
    void modifyIntelligence(int delta);
    void modifyDexterity(int delta);
    void modifyCharisma(int delta);
    bool getIsExploring() const;
    void setIsExploring();
    bool getIsInBattle() const;
    void setIsInBattle();
    bool getIsOptedInForBattles() const;
    void setIsOptedInForBattles(bool value);
    bool operator==(const ICharacter &other) const;
    virtual int getAttackValue() = 0;
    virtual int getDefenceValue() = 0;
    virtual ~ICharacter() {}
  protected:
    ICharacter();
    ICharacter(string description, Attributes attributes)
      : description(description),
        attributes(attributes),
        isInBattle(false),
        isOptedInForBattles(false) {}
    string description;
    Attributes attributes;
    bool isInBattle;
    bool isOptedInForBattles;
    void clampZero(int &value);
  };
}

#endif
