#ifndef GIANTSTRENGTH_H
#define GIANTSTRENGTH_H
#include <iostream>
#include <string>
#include <memory>
#include "Enchantment.h"

class GiantStrength;
typedef std::shared_ptr<GiantStrength> GiantStrengthPtr;

class GiantStrength : public Enchantment {
 public:
  GiantStrength(bool owner);
  ~GiantStrength();
};

#endif
