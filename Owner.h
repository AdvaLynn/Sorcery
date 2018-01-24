#ifndef OWNER_H
#define OWNER_H
#include <string>
#include <iostream>
#include <memory>

#include "Hand.h"
#include "Deck.h"
#include "Card.h"
#include "Graveyard.h"
#include "Board.h"

class Owner;
typedef std::shared_ptr<Owner> OwnerPtr;

class Owner{
  std::string name;
  int magic;
  int health;
  Hand hand;
  DeckPtr deck;
  Graveyard graveyard;
  Board board;
  void displayBorder(int p, std::vector<std::string> &row);
 public:
  Owner(std::string name, DeckPtr deck);
  Board &getBoard();
  Graveyard &getGraveyard();
  Deck &getDeck();
  Hand &getHand();
  
  std::string getName() const;
  void setName(std::string name);
  void addMagic(int i);
  int getMagic();
  void addHealth(int i);
  int getHealth();
  void displayOwner(int p);
  void draw();
  ~Owner();
};

#endif

