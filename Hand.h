#ifndef HAND_H
#define HAND_H
#include <string>
#include <vector>
#include <memory>
#include "ascii_graphics.h"
#include "Card.h"
#include "Ritual.h"
#include "Minion.h"
#include "ActivatedAbilities.h"
#include "TriggeredAbilities.h"

class Hand;
typedef std::shared_ptr<Hand> HandPtr;

class Hand {
  std::vector<CardPtr> cards;
 public:
  std::vector<CardPtr> getCards();
  void attach(CardPtr c);
  CardPtr detach(int i);
  void displayHand();
  Hand();
  ~Hand();
};

#endif

