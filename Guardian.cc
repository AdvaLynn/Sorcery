#include "Guardian.h"

Guardian::Guardian(bool owner)
  : TriggeredAbilities{"Guardian", "Prevents player from being attacked when this card is on the board", owner, 2, 1, 4} {}

Guardian::~Guardian(){}
