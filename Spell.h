#ifndef SPELL_H
#define SPELL_H
#include <string>
#include <memory>
#include "Card.h"

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class Spell : public Card {
 protected:
  Spell(std::string name, std::string descript, bool owner, int origCost);
 public:
  virtual ~Spell();
};

#endif

