#ifndef MAGICLESS_
#define MAGICLESS_
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Enchantment.h"

class Magicless;
typedef std::shared_ptr<Magicless> MagiclessPtr;

class Magicless : public Enchantment {
 public:
  Magicless(bool owner);
  ~Magicless();
};

#endif
