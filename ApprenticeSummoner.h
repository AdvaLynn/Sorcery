#ifndef APPSUM_H
#define APPSUM_H
#include <vector>
#include <string>
#include <memory>
#include "ActivatedAbilities.h"

class ApprenticeSummoner;
typedef std::shared_ptr<ApprenticeSummoner> ApprenticeSummonerPtr;

class ApprenticeSummoner : public ActivatedAbilities {
 public:
  ApprenticeSummoner(bool owner);
  ~ApprenticeSummoner();
};

#endif

