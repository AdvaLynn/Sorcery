#ifndef DISENCHANT_H
#define DISENCHANT_H
#include <string>
#include <iostream>
#include <memory>
#include "Spell.h"

class Disenchant;
typedef std::shared_ptr<Disenchant> DisenchantPtr;

class Disenchant : public Spell {
public:
  Disenchant(bool owner);
  ~Disenchant();
};

#endif
