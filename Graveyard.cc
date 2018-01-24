#include "Graveyard.h"

using namespace std;

Graveyard::Graveyard(){}

void Graveyard::attach(MinionPtr m) {
  minions.emplace_back(m);
}

MinionPtr Graveyard::detach() {
  MinionPtr m = minions[minions.size()-1];
  minions.pop_back();
  return m;
}

vector<MinionPtr> &Graveyard::getMinions(){
  return minions;
}

Graveyard::~Graveyard(){}
