#include "Silence.h"

Silence::Silence(bool owner)
  :Enchantment{"Silence", "Enchanted minions cannot use abilities", owner, 1}{}
Silence::~Silence(){}
