#include "Disenchant.h"

Disenchant::Disenchant(bool owner)
  : Spell{"Disenchant", "Destroy the top enchantment on target minion", owner, 1}{}
Disenchant::~Disenchant() {}
