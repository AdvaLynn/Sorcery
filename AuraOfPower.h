#ifndef AURAOFPOWER_H
#define AURAOFPOWER_H
#include <iostream>
#include <string>
#include <memory>
#include "Ritual.h"

class AuraOfPower;
typedef std::shared_ptr<AuraOfPower> AuraOfPowerPtr;

class AuraOfPower : public Ritual{  
 public:
  AuraOfPower(bool owner);
  ~AuraOfPower();
};

#endif
