#include "Magicless.h"

using namespace std;

Magicless::Magicless(bool owner)
  : Enchantment{"Magicless", "Decreases opponent's magic by 1", owner, 1}{}
Magicless::~Magicless() {}
