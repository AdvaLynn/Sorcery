#ifndef UNSUMMON_H
#define UNSUMMON_H
#include <string>
#include <iostream>
#include <memory>
#include "Spell.h"

class Unsummon;
typedef std::shared_ptr<Unsummon> UnsummonPtr;

class Unsummon : public Spell {
 public:
  Unsummon(bool owner);
  ~Unsummon();
};

#endif
