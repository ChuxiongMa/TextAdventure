#include "Combat.hpp"

#include <random>
#include <assert.h>
#include <algorithm>

#include <iostream>

unique_ptr<textadventure::Combat> textadventure::Combat::instance;

static const int EXPERIENCE_WIN_FACTOR = 100;
static const int MONEY_WIN_FACTOR = 50;

textadventure::Combat::Combat() {
  generator.seed(time(NULL));
}

textadventure::Combat &textadventure::Combat::getInstance() {
  if (instance.get() == nullptr) {
    instance = unique_ptr<textadventure::Combat>(new Combat());
  }
  return *instance;
}

bool textadventure::Combat::startBattle(ICharacter *player1, ICharacter *player2OrNPC) {
  if (player1->getIsOptedInForBattles() == false ||
      player2OrNPC->getIsOptedInForBattles() == false) {
    return false;
  }
  if (player1->getIsInBattle() == true ||
      player2OrNPC->getIsInBattle() == true) {
    return false;
  }

  Turn turn = PLAYER1;
  if (player2OrNPC->getDexterity() > player1->getDexterity()) {
    turn = PLAYER2;
  } else if (player2OrNPC->getDexterity() == player1->getDexterity()) {
    std::uniform_int_distribution<int> pickPlayer(0,1);
    int decideFirst = pickPlayer(generator);
    if (decideFirst == 1) {
      turn = PLAYER2;
    }
  }

  Battle battle = Battle(*player1, *player2OrNPC, turn);

  battles.push_back(battle);
  player1->setIsInBattle();
  player2OrNPC->setIsInBattle();
  return true;
}

bool textadventure::Combat::performAttack(textadventure::ICharacter &attacker) {
  textadventure::Battle *battle = this->getBattle(attacker);
  if (battle == nullptr) {
    return false;
  }

  int attackerIndex = battle->getCharacterIndex(attacker);
  int defenderIndex = (attackerIndex + 1) % 2;
  ICharacter &defender = battle->getCharacter(defenderIndex);

  if (!battle->isTurn(attacker)) {
    return false;
  }

  int attackMax = attacker.getAttackValue() + attacker.getStrength();
  int totalAttack = 0;
  std::uniform_int_distribution<int> attackValue(attackMax / 2, attackMax);
  totalAttack += attackValue(generator);
  std::uniform_int_distribution<int> dexterityBonus(0, attacker.getDexterity());
  totalAttack += dexterityBonus(generator);

  totalAttack -= defender.getDefenceValue();
  std::uniform_int_distribution<int> defendDexterity(0, defender.getDexterity());
  totalAttack -= defendDexterity(generator);
  if (totalAttack < 0) {
    totalAttack = 0;
  }

  defender.modifyHealth(totalAttack * -1);
  battle->endTurn();

  if (defender.getHealth() == 0) {
    defeatedCleanUp(attacker, defender);
    endBattle(attacker);
    return true;
  }

  // if user is attacking an NPC, can perform NPC attack right away
  if (dynamic_cast<NPC *>(&defender) != nullptr) {
    performAttack(defender);
  }

  return true;
}

void textadventure::Combat::defeatedCleanUp(ICharacter &winner, ICharacter &loser) {
  // NPC won
  if (dynamic_cast<Player *>(&winner) == nullptr) {
    NPC *winningNPC = dynamic_cast<NPC *>(&winner);
    Player *defeatedPlayer = dynamic_cast<Player *>(&loser);
    defeatedPlayer->modifyExperience(winningNPC->getExperienceGivenOnDefeat() * -1);
    return;
  }

  // Player won
  Player *winningPlayer = dynamic_cast<Player *>(&winner);
  if (dynamic_cast<NPC *>(&loser) != nullptr) {
    // against NPC
    NPC *defeatedNPC = dynamic_cast<NPC *>(&loser);
    winningPlayer->modifyExperience(defeatedNPC->getExperienceGivenOnDefeat());
    winningPlayer->modifyMoney(defeatedNPC->getMoneyGivenOnDefeat());

  } else if (dynamic_cast<Player *>(&loser) != nullptr) {
    // against another NPC
    Player *defeatedPlayer = dynamic_cast<Player *>(&loser);
    int experienceGain = defeatedPlayer->getLevel() * EXPERIENCE_WIN_FACTOR;
    winningPlayer->modifyExperience(experienceGain);
    defeatedPlayer->modifyExperience(experienceGain * -1);
    int moneyGain = defeatedPlayer->getLevel() * MONEY_WIN_FACTOR;
    winningPlayer->modifyExperience(moneyGain);
    defeatedPlayer->modifyExperience(moneyGain * -1);
  }
}


bool textadventure::Combat::attemptRun(ICharacter &player) {
  textadventure::Battle *battle = this->getBattle(player);
  if (battle == nullptr) {
    return false;
  }

  if (!battle->isTurn(player)) {
    return false;
  }

  std::uniform_int_distribution<int> run(0, player.getIntelligence());
  std::uniform_int_distribution<int> blockRun(0, battle->getOtherCharacter(player).getIntelligence());
  int runValue = run(generator);
  int blockValue = blockRun(generator);

  bool success = (runValue >= blockValue);
  if (success) {
    endBattle(player);
  } else {
    assert(false);
  }
  battle->endTurn();
  return success;
}

bool textadventure::Combat::endBattle(ICharacter &playerOrNPC) {
  textadventure::Battle *battle = this->getBattle(playerOrNPC);
  if (battle == nullptr) {
    return false;
  } else {
    battle->getCharacter(0).setIsExploring();
    battle->getCharacter(1).setIsExploring();
    battles.erase(std::remove_if(battles.begin(), battles.end(),
        [&playerOrNPC](Battle &b){ return b.getCharacter(0) == playerOrNPC || b.getCharacter(1) == playerOrNPC; }),
        battles.end());
    return true;
  }
}

textadventure::Battle *textadventure::Combat::getBattle(ICharacter &player) {
  for (Battle &battle : battles) {
    if (battle.getCharacter(0) == player || battle.getCharacter(1) == player) {
      return &battle;
    }
  }
  return nullptr;
}


textadventure::Battle::Battle(ICharacter &character1, ICharacter &character2, Turn turn)
  : turn(turn)
{
  characters[0] = &character1;
  characters[1] = &character2;
}

textadventure::ICharacter &textadventure::Battle::getCharacter(int index) {
  assert(index >= 0 && index <= 1);
  return *(characters[index]);
}

int textadventure::Battle::getCharacterIndex(ICharacter &character) {
  if (*(characters[0]) == character) {
    return 0;
  } else if (*(characters[1]) == character) {
    return 1;
  }
  assert(false);
  return -1;
}

textadventure::ICharacter &textadventure::Battle::getOtherCharacter(ICharacter &character) {
  if (*(characters[0]) == character) {
    return *(characters[1]);
  } else if (*(characters[1]) == character) {
    return *(characters[0]);
  }
  assert(false);
}

bool textadventure::Battle::isTurn(ICharacter &character) {
  return (turn == getCharacterIndex(character));
}

void textadventure::Battle::endTurn() {
  turn = static_cast<Turn>((turn + 1) % 2);
}
