#include "NovicePyromancer.h"

NovicePyromancer::NovicePyromancer(bool owner)
  : ActivatedAbilities{"Novice Pyromancer", "Deal 1 damage to target minion", owner, 1, 0, 1, 1}{}
NovicePyromancer::~NovicePyromancer(){}
