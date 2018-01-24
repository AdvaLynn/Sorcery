#include "PotionSeller.h"

PotionSeller::PotionSeller(bool owner)
  :TriggeredAbilities{"Potion Seller", "At the end of your turn, all your minions gain +0/+1.", owner, 2, 1, 3} {}

PotionSeller::~PotionSeller(){}
