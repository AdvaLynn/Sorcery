#ifndef EARTHELEMENTAL_H
#define EARTHELEMENTAL_H
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include "Minion.h"

class EarthElemental;
typedef std::shared_ptr<EarthElemental> EarthElementalPtr;

class EarthElemental : public Minion{
 public:
  EarthElemental(bool owner);
  ~EarthElemental();
};

#endif
