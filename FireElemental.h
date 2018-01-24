#ifndef FIREELEMENTAL_H
#define FIREELEMENTAL_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "TriggeredAbilities.h"

class FireElemental;
typedef std::shared_ptr<FireElemental> FireElementalPtr;

class FireElemental : public TriggeredAbilities {
 public:
  FireElemental(bool owner);
  ~FireElemental();
};

#endif

