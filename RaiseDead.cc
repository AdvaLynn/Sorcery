#include "RaiseDead.h"

RaiseDead::RaiseDead(bool owner)
  : Spell{"Raise Dead", "Resurrect the top minion in your graveyard", owner, 1} {}
RaiseDead::~RaiseDead(){}

