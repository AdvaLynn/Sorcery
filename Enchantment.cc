#include "Enchantment.h"

using namespace std;

Enchantment::Enchantment(string name, string descript, bool owner, int origCost)
  : Card{name,"Enchantment", descript, owner, origCost}{}

Enchantment::~Enchantment(){}
