#include "ActivatedAbilities.h"

using namespace std;

ActivatedAbilities::ActivatedAbilities(std::string name, std::string descript, bool owner, int origCost, int origAttack, int origDef, int origActCost)
  : Minion{name, descript, owner, origCost, origAttack, origDef},
    origActCost{origActCost}{
      currActCost = origActCost;
    }
ActivatedAbilities::~ActivatedAbilities(){}

void ActivatedAbilities::receiveEnchantFrom(EnchantmentPtr e) {
  if (e->getName() == "Giant Strength") {
    addCurrAttack(2);
    addCurrDef(2);
  } else if (e->getName() == "Magic Fatigue") {
    currActCost += 2;
  } else if  (e->getName() == "Silence") {
    setCanUseAbility(false);
  }
  attachEnchantment(e);
}

bool ActivatedAbilities::removeEnchantment(){
  EnchantmentPtr e = enchants[enchants.size()-1];
  if(e->getName() == "Giant Strength"){
    addCurrAttack(-2);
    addCurrDef(-2);
    if(getCurrDef() <= 0) return false;
  }else if(e->getName() == "Magic Fatigue"){
    currActCost -= 2;
  }else if(e->getName() == "Silence"){
    setCanUseAbility(true);
  }
  enchants.pop_back();
  return true;
}

int ActivatedAbilities::getCurrActCost() {
  return currActCost;
}
