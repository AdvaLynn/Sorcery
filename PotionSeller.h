#ifndef POTIONSELLER_H
#define POTIONSELLER_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "TriggeredAbilities.h"

class PotionSeller;
typedef std::shared_ptr<PotionSeller> PotionSellerPtr;

class PotionSeller : public TriggeredAbilities {
 public:
  PotionSeller(bool owner);
  ~PotionSeller();
};

#endif

