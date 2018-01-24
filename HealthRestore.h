#ifndef HEALTH_
#define HEALTH_
#include <iostream>
#include <string>
#include <memory>
#include "Ritual.h"

class HealthRestore;
typedef std::shared_ptr<HealthRestore> HealthRestorePtr;

class HealthRestore : public Ritual{  
 public:
  HealthRestore(bool owner);
  ~HealthRestore();
};

#endif
