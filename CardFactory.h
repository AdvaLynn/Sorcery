#ifndef CARDFACTORY_H
#define CARDFACTORY_H
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include "Card.h"

class CardFactory;
typedef std::shared_ptr<CardFactory> CardFactoryPtr;

class CardFactory {
  std::string filename;
  bool turn;
 private:
  CardPtr makeCard(std::string n);
 public:
  CardFactory(std::string filename, bool turn);
  std::vector <CardPtr> makeDeck();
  ~CardFactory();
};

#endif
