#include "Unsummon.h"

using namespace std;

Unsummon::Unsummon(bool owner)
  : Spell{"Unsummon", "Put target minion on the bottom of its owner's deck", owner, 1}{}
Unsummon::~Unsummon() {}

