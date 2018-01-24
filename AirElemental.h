#ifndef AIRELEMENT_H
#define AIRELEMENT_H
#include <vector>
#include "Minion.h"
#include <memory>
#include <string>

class AirElemental;
typedef std::shared_ptr<AirElemental> AirElementalPtr;

class AirElemental : public Minion {
 public:
  AirElemental(bool owner);
  ~AirElemental();

};

#endif

  
