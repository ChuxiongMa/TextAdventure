#include "NPC.hpp"
#include <algorithm>

using namespace std;

// constructor for NPCs that can't be fought
textadventure::NPC::NPC(int id, vector<string> keywords, string shortDescription, string longDescription, string description)
  : ICharacter(description, Attributes(0)),
    id(id),
    keywords(keywords),
    shortDescription(shortDescription),
    longDescription(longDescription),
    experienceGivenOnDefeat(0),
    money(0),
    attack(0),
    defence(0)
{
  setIsOptedInForBattles(false);
}

// constructor for fightable NPCs
textadventure::NPC::NPC(int id, vector<string> keywords, string shortDescription, string longDescription, string description,
    Attributes attributes, int experienceGivenOnDefeat, int money, int attack, int defence)
  : ICharacter(description, attributes),
    id(id),
    keywords(keywords),
    shortDescription(shortDescription),
    longDescription(longDescription),
    experienceGivenOnDefeat(experienceGivenOnDefeat),
    money(money),
    attack(attack),
    defence(defence)
{
  setIsOptedInForBattles(true);
}

// constructor for fightable NPCs simplified
textadventure::NPC::NPC(int id, vector<string> keywords, string shortDescription, string longDescription, string description,
    int attackMax, int defenceMax)
  : ICharacter(description, Attributes(0)),
    id(id),
    keywords(keywords),
    shortDescription(shortDescription),
    longDescription(longDescription)
{
  setIsOptedInForBattles(true);
  // arbitrary stat creation
  std::default_random_engine generator;
  std::uniform_int_distribution<int> generateAttack(1, attackMax);
  std::uniform_int_distribution<int> generateDefence(1, defenceMax);
  std::uniform_int_distribution<int> generateHealth(1, attackMax + defenceMax);
  attack = generateAttack(generator);
  defence = generateDefence(generator);
  money = (attack + defence) * 2;
  experienceGivenOnDefeat = money * 10;
  attributes.health = generateHealth(generator);
}

int textadventure::NPC::getId() const {
  return id;
}

string textadventure::NPC::getShortDescription() const {
  return shortDescription;
}

string textadventure::NPC::getLongDescription() const {
  return longDescription;
}

vector<string> textadventure::NPC::getKeywords() const {
  return keywords;
}

bool textadventure::NPC::containsKeyword(string keyword) const {
  return (std::find(keywords.begin(), keywords.end(), keyword) != keywords.end());
}

int textadventure::NPC::getExperienceGivenOnDefeat() const {
  return experienceGivenOnDefeat;
}

int textadventure::NPC::getMoneyGivenOnDefeat() const {
  return money;
}

int textadventure::NPC::getAttackValue() {
  return attack;
}
int textadventure::NPC::getDefenceValue() {
  return defence;
}
