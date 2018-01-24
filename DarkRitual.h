#ifndef DARKRITUAL_H
#define DARKRITUAL_H
#include <iostream>
#include <string>
#include <memory>
#include "Ritual.h"

class DarkRitual;
typedef std::shared_ptr<DarkRitual> DarkRitualPtr;

class DarkRitual : public Ritual{
 public:
  DarkRitual(bool owner);
  ~DarkRitual();
};

#endif
