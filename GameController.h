#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <memory>

#include "Owner.h"

#include "ascii_graphics.h"
#include "Blizzard.h"
#include "Banish.h"
#include "AirElemental.h"
#include "FireElemental.h"
#include "ApprenticeSummoner.h"
#include "PotionSeller.h"
#include "EarthElemental.h"
#include "NovicePyromancer.h"
#include "MasterSummoner.h"
#include "CardFactory.h"

class GameController;
typedef std::shared_ptr<GameController> GameControllerPtr;

class GameController{

  OwnerPtr o1;
  OwnerPtr o2;

  //return types for getState()
  /*
  const int DRAW  = 0;
  const int ONE_WIN = 1;
  const int TWO_WIN = 2;
  const int IN_PROGRESS = 3;
  */
  bool testing = false;
  bool turn = true;
  int draw = 1;

 public:
  
  GameController(OwnerPtr o1, OwnerPtr o2, bool testing);

  //fetch(int j) : fetches minion i.
  MinionPtr fetch(OwnerPtr o, int i);

  //fetch(Owner *o, int i); fetches card from Hand.
  CardPtr fetchHand(OwnerPtr o, int i);

  //reset() : resets minions' hasAttacked to false
  void reset();
  
  void startGame(std::vector<std::string> fileargs);

 private:
  // GAME FLOW METHODS:
  void startGame_helper(std::string cmd);

  void displaySorcery();
  void printHelp();
    
  OwnerPtr getAP();
  OwnerPtr getNAP();
  
  // USE: the use command 
  void Use(int i, int p, int j);  // ADD BOOL OWNER LATER
  void Use(int i);

  // BOARD ADJUSTMENT METHODS:
  bool summon(int num, MinionPtr summoned);
  void bury(MinionPtr m);

  // TRIGGER METHODS
  void triggerPotionSeller();
  void triggerDarkRitual();

  void triggerFireElemental();
  void triggerAuraOfPower();
  bool triggerStandstill();
  
  // PLAY METHODS
  void playBlizzard();
  void playRecharge();
  void playRaiseDead();

  // ATTACK: the attack command
  void Attack(int i);
  void Attack(int i, int j);
  
  // PLAY: the play command
  void Play(int i);
  void Play(int i, int, std::string j);

  // UNSUMMON: when the spell unsummon is called.
  void unsummon(MinionPtr m, OwnerPtr o);
  
};

#endif
