#include "TriggeredAbilities.h"
using namespace std;

TriggeredAbilities::TriggeredAbilities(string name, string descript, bool owner, int origCost, int origAttack, int origDef)
  : Minion{name, descript, owner, origCost, origAttack, origDef}{}

TriggeredAbilities::~TriggeredAbilities(){}

void TriggeredAbilities::receiveEnchantFrom(EnchantmentPtr e) {
  if (e->getName() == "Giant Strength") {
    addCurrAttack(2);
    addCurrDef(2); 
    attachEnchantment(e);
  } else{
    attachEnchantment(e);
  }
}

bool TriggeredAbilities::removeEnchantment() {
  EnchantmentPtr e = enchants[enchants.size()-1];
  if (e->getName() == "Giant Strength") {
    addCurrAttack(-2);
    addCurrDef(-2);
    if(getCurrDef() <= 0) return false;
  }
  enchants.pop_back();
  return true;
}
