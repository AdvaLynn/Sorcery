#include "HealthRestore.h"
HealthRestore::HealthRestore(bool owner)
  :Ritual{"Health Restore", "Gains 1 health when minion under own control dies", owner, 2, 1, 3}{}
HealthRestore::~HealthRestore(){}
