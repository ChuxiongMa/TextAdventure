#ifndef NPC_H
#define NPC_H

#include <string>
#include <vector>

#include "Attributes.hpp"
#include "ICharacter.hpp"

using namespace std;

namespace textadventure {
  class NPC : public ICharacter {
  public:
    NPC(int id, vector<string> keywords, string shortDescription, string longDescription, string description);
    NPC(int id, vector<string> keywords, string shortDescription, string longDescription, string description,
        Attributes attributes, int experienceGivenOnDefeat, int money, int attack, int defence);
    NPC(int id, vector<string> keywords, string shortDescription, string longDescription, string description,
        int attackMax, int defenceMax);
    int getId() const;
    string getShortDescription() const;
    string getLongDescription() const;
    vector<string> getKeywords() const;
    bool containsKeyword(string keyword) const;

    bool canFight() const;
    int getExperienceGivenOnDefeat() const;
    int getMoneyGivenOnDefeat() const;

    virtual int getAttackValue() override;
    virtual int getDefenceValue() override;
  private:
    int id;
    string shortDescription;
    string longDescription;
    vector<string> keywords;
    int experienceGivenOnDefeat;
    int money;
    int attack;
    int defence;
  };
}


#endif
