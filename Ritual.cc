#include "Ritual.h"

Ritual::Ritual(std::string name, std::string descript, bool owner, int origCost, int activateCost, int origCharge)
  : Card{name, "Ritual", descript, owner, origCost},
   activateCost{activateCost}, origCharge{origCharge} {
     currCharge = origCharge;
   }

void Ritual::charge(int i) {
  currCharge += i;
}

int Ritual::getCurrCharge() {
  return currCharge;
}

int Ritual::getCurrActCost() {
  return activateCost;
}

Ritual::~Ritual() {}
