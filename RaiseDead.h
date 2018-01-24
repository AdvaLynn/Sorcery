#ifndef RAISEDEAD_H
#define RAISEDEAD_H
#include <iostream>
#include <string>
#include <memory>
#include "Spell.h"

class RaiseDead;
typedef std::shared_ptr<RaiseDead> RaiseDeadPtr;

class RaiseDead : public Spell{
  public:
    RaiseDead(bool owner);
    ~RaiseDead();
};

#endif
