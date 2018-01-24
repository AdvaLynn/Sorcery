#ifndef MAGICFATIGUE_H
#define MAGICFATIGUE_H
#include <iostream>
#include <string>
#include <memory>
#include "Enchantment.h"

class MagicFatigue;
typedef std::shared_ptr<MagicFatigue> MagicFatiguePtr;

class MagicFatigue : public Enchantment {
 public:
  MagicFatigue(bool owner);
  ~MagicFatigue();
};

#endif
