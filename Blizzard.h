#ifndef BLIZZARD_H
#define BLIZZARD_H
#include <string>
#include <iostream>
#include <memory>
#include "Spell.h"

class Blizzard;
typedef std::shared_ptr<Blizzard> BlizzardPtr;

class Blizzard : public Spell {
 public:
  Blizzard(bool owner);
  ~Blizzard();

};

#endif
