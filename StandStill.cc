#include "StandStill.h"
using namespace std;

StandStill::StandStill(bool owner)
  : Ritual{"Standstill", "Whenever a minion enters a play, destroy it", owner, 4, 2, 4}{}

StandStill::~StandStill() {}
