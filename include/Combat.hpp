#ifndef COMBAT_H
#define COMBAT_H

#include "Player.hpp"
#include <memory>
#include "NPC.hpp"
#include <random>

/*
 * Current combat mechanics:
 *    player with highest dexterity attacks first; random if equal
 *    damage = random[(weapon attack + strength)/2 -> (weapon attack + strength)]
 *              + random[0 -> attacker dexterity] - defender armor - random[0 -> defender dexterity]
 */


namespace textadventure {
  enum Turn {
    PLAYER1 = 0,
    PLAYER2 = 1
  };

  class Battle{
  public:
    Battle(ICharacter &character1, ICharacter &character2, Turn turn);
    ICharacter &getCharacter(int index);
    int getCharacterIndex(ICharacter &character);
    ICharacter &getOtherCharacter(ICharacter &character);
    bool isTurn(ICharacter &character);
    void endTurn();
  private:
    // NPCs always go second
    ICharacter *characters[2];
    Turn turn;
  };

  class Combat {
  public:
    static Combat &getInstance();
    /**
     * returns false if either player is not opted in to fight
     */
    bool startBattle(ICharacter *player1, ICharacter *player2OrNPC);
    /**
     * Will automatically perform NPC attack if a Player vs NPC battle
     * return false if not performed (because it's not that player's turn)
     */
    bool performAttack(ICharacter &attacker);
    /**
     * return true if successful. Battle is then ended
     */
    bool attemptRun(ICharacter &player);
    bool endBattle(ICharacter &playerOrNPC);
  private:
    Combat();
    static unique_ptr<Combat> instance;
    vector<Battle> battles;
    std::default_random_engine generator;
    Battle *getBattle(ICharacter &player);
    void defeatedCleanUp(ICharacter &winner, ICharacter &loser);
  };
}


#endif
