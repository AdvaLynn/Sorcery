#include "Recharge.h"
 using namespace std;

 Recharge::Recharge(bool owner)
   : Spell{"Recharge", "Your ritual gains 3 charges", owner, 1} {}

 Recharge::~Recharge() {}
