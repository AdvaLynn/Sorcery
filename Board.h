#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <iostream>
#include <vector>

#include "Minion.h"
#include "Ritual.h"
#include "ascii_graphics.h"
#include "ActivatedAbilities.h"
#include "TriggeredAbilities.h"
#include "Spell.h"
#include "Ritual.h"
#include "Enchantment.h"

class Board;
typedef std::shared_ptr<Board> BoardPtr;

class Board{
  std::vector<MinionPtr> minions;
  RitualPtr ritual;

 public:
  Board();
  ~Board();
  void attach(MinionPtr);
  void detach(MinionPtr);
  void setRitual(RitualPtr);
  RitualPtr getRitual();
  void displayBoard();
  std::vector<MinionPtr> &getMinions();
};
#endif
