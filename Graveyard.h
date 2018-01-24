#ifndef GRAVEYARD_H
#define GRAVEYARD_H
#include <vector>
#include <string>
#include <fstream>
#include <memory>

#include "Minion.h"

class Graveyard;
typedef std::shared_ptr<Graveyard> GraveyardPtr;

class Graveyard {
  std::vector<MinionPtr> minions;
 public:
  void attach(MinionPtr);
  MinionPtr detach();
  std::vector<MinionPtr> &getMinions();
  Graveyard();
  ~Graveyard();
};

#endif
