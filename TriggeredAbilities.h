#ifndef TRIGGEREDABILITIES_H
#define TRIGGEREDABILITIES_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Minion.h"
#include "Enchantment.h"

class TriggeredAbilities;
typedef std::shared_ptr<TriggeredAbilities> TriggeredAbilitiesPtr;

class TriggeredAbilities : public Minion{
 protected:
  TriggeredAbilities(std::string name, std::string descript, bool owner, int origCost, int origAttack, int origDef);
 public:
  void receiveEnchantFrom(EnchantmentPtr e) override;
  bool removeEnchantment() override;
  virtual ~TriggeredAbilities();
};

#endif
