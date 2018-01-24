#include "MasterSummoner.h"
using namespace std;
MasterSummoner::MasterSummoner(bool owner)
  :ActivatedAbilities{"Master Summoner", "Summon up to three 1/1 air elementals", owner, 3,2,3,2} {}
MasterSummoner::~MasterSummoner(){}
