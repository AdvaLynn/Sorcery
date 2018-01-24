#ifndef RECHARGE_H
#define RECHARGE_H
#include <iostream>
#include <string>
#include <memory>
#include "Spell.h"

class Recharge;
typedef std::shared_ptr<Recharge> RechargePtr;

class Recharge : public Spell {
 public:
  Recharge(bool owner);
  ~Recharge();
};

#endif
