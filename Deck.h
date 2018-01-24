#ifndef DECK_H
#define DECK_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <algorithm>

#include "Card.h"

class Deck;
typedef std::shared_ptr<Deck> DeckPtr;

class Deck {
  std::vector<CardPtr> deckCards;
  bool testing;
 public: 
  Deck(std::vector<CardPtr> deckCards, bool testing);
  std::vector<CardPtr>getCards();
  void attach(CardPtr c);
  void shuffle();
  CardPtr detach();
  ~Deck();
};

#endif

