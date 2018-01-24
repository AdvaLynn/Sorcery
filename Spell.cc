#include "Spell.h"
using namespace std;

Spell::Spell(string name, string descript, bool owner, int origCost)
  : Card{name, "Spell", descript, owner, origCost}{}
Spell::~Spell(){}
