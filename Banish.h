#ifndef BANISH_H
#define BANISH_H
#include <iostream>
#include <string>
#include <memory>
#include "Spell.h"

class Banish;
typedef std::shared_ptr<Banish> BanishPtr;

class Banish : public Spell {
 public:
  Banish(bool owner);
  ~Banish();
};

#endif
