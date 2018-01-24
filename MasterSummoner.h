#ifndef MASTERSUMMONER_H
#define MASTERSUMMONER_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "ActivatedAbilities.h"

class MasterSummoner;
typedef std::shared_ptr<MasterSummoner> MasterSummonerPtr;

class MasterSummoner : public ActivatedAbilities {
 public:
  MasterSummoner(bool owner);
  ~MasterSummoner();
};


#endif
