#include "Banish.h"

using namespace std;

Banish::Banish(bool owner)
  : Spell{"Banish", "Destroy target minion or ritual", owner, 2}{}
Banish::~Banish() {}
