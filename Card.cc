#include "Card.h"

using namespace std;

string Card::getType() const {
  return type;
}
string Card::getName() const {
  return name;
}

bool Card::getOwner(){
  return owner;
}

void Card::toggleOwner(){
  owner = !owner;
}

int Card::getOrigCost() const {
  return origCost;
}

string Card::getDescription() const {
  return descript;
}

Card::Card(string name, string type, string descript, bool owner, int origCost)
  : name{name}, type{type}, descript{descript}, owner{owner}, origCost{origCost}{}

Card::~Card(){}

