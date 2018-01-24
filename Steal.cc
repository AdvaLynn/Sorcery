#include "Steal.h"
Steal::Steal(bool owner)
  :Spell{"Steal", "Steal one of your opponent's cards from hand", owner, 2}{}
Steal::~Steal(){}
