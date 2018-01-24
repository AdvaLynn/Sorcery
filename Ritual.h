#ifndef RITUAL_H
#define RITUAL_H
#include <iostream>
#include <string>
#include "Card.h"

class Ritual;
typedef std::shared_ptr<Ritual> RitualPtr;

class Ritual : public Card{
  int activateCost;
  const int origCharge;
  int currCharge;

 protected:
  Ritual(std::string name, std::string descript, bool owner, int origCost, int activateCost, int origCharge);
 public:
  int getCurrActCost();
  void charge(int i);
  int getCurrCharge();
  virtual ~Ritual();
};

#endif
