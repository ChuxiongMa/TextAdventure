#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

namespace textadventure {

  class Attributes {
  public:
    Attributes(int defaultVal) :
        Attributes(defaultVal, defaultVal, defaultVal,
            defaultVal, defaultVal, defaultVal) {};
    Attributes(int level, int health, int strength,
        int intelligence, int dexterity, int charisma) :
          level(level), health(health), strength(strength),
          intelligence(intelligence), dexterity(dexterity),
          charisma(charisma) {};
    bool meetsRequirements(Attributes &requirements) {
      return (this->level >= requirements.level &&
          this->health >= requirements.health &&
          this->strength >= requirements.strength &&
          this->intelligence >= requirements.intelligence &&
          this->dexterity >= requirements.dexterity &&
          this->charisma >= requirements.charisma);
    }
    bool operator==(const Attributes &other) const {
      return (level == other.level &&
          health == other.health &&
          strength == other.strength &&
          intelligence == other.intelligence &&
          dexterity == other.dexterity &&
          charisma == other.charisma);
    }
    int level;
    int health;
    int strength;
    int intelligence;
    int dexterity;
    int charisma;
  };
}

#endif
