#ifndef STANDSTILL_H
#define STANDSTILL_H
#include <iostream>
#include <string>
#include <memory>
#include "Ritual.h"

class StandStill;
typedef std::shared_ptr<StandStill> StandStillPtr;

class StandStill : public Ritual {
 public:
  StandStill(bool owner);
  ~StandStill();
};

#endif
