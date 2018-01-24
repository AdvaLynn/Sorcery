#ifndef ACTIVATEDABILITIES_H
#define ACTIVATEDABILITIES_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Minion.h"
#include "Enchantment.h"

class ActivatedAbilities;
typedef std::shared_ptr<ActivatedAbilities> ActivatedAbilitiesPtr;

class ActivatedAbilities : public Minion{
  const int origActCost;
  int currActCost;
 protected:
  ActivatedAbilities(std::string name, std::string descript, bool owner, int origCost, int origAttack, int origDef, int origActCost);

 public:
  void receiveEnchantFrom(EnchantmentPtr e) override;
  bool removeEnchantment() override;
  int getCurrActCost();
  virtual ~ActivatedAbilities();
};

#endif
