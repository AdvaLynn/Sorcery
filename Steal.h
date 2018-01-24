#ifndef STEAL_
#define STEAL_
#include <iostream>
#include <string>
#include <memory>
#include "Spell.h"

class Steal;
typedef std::shared_ptr<Steal> StealPtr;

class Steal : public Spell{  
 public:
  Steal(bool owner);
  ~Steal();
};

#endif
