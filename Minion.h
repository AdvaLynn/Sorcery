#ifndef MINION_H
#define MINION_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Card.h"
#include "Enchantment.h"
#include "ascii_graphics.h"

class Banish;
class Ritual;
class Blizzard;
class FireElemental;
class PotionSeller;
class NovicePyromancer;
class ApprenticeSummoner;
class MasterSummoner;
class GiantStrength;
class MagicFatigue;
class Silence;
class AuraOfPower;
class StandStill;
class Enchantment;
class AirElemental;

class Minion;
typedef std::shared_ptr<Minion> MinionPtr;

class Minion : public Card {
  const int origAttack;
  const int origDef;
  int currCost;
  int currAttack;
  int currDef;
  bool hasAttacked = false;
  bool canUseAbility = true;

  int hasMagicless = 0;
  
  void displayMinion_helper(int start, int end, std::vector <card_template_t> &buffer);
 public:
  void addMagicless(int i);
  int getMagicless();
  std::vector<EnchantmentPtr> enchants;
  bool receiveAttackFrom(MinionPtr m, bool ability);

  bool receiveAttackFrom(Blizzard &b);
  
  // SPELLS
  // returns true if minion does not die after receiving attack, false o/w
  bool receiveSpellFrom(CardPtr c);

  std::vector<EnchantmentPtr> getEnchantments();
  
  virtual void receiveEnchantFrom(EnchantmentPtr e);
  virtual bool removeEnchantment();
  void attachEnchantment(EnchantmentPtr e);

  void receiveRitualFrom(Ritual &r);
  // RITUAL
  void receiveRitualFrom(AuraOfPower &a);
  void receiveRitualFrom(StandStill &s);

  // attacked(): changes hasAttacked field to true;
  void attacked(bool reset = false);

  // reset(): resets minion back to original field values.
  void reset();

  // getCurrAttack(): returns current attack.
  int getCurrAttack();
  void addCurrAttack(int i);
  int getCurrDef();
  void addCurrDef(int i);

  // getasAttacked()
  bool getHasAttacked();

  bool getCanUseAbility();
  void setCanUseAbility(bool in);

  // displays minion with attached enchantments
  void displayMinion();

  // DTOR
  virtual ~Minion();
 protected:
  Minion(std::string name, std::string descript, bool owner, int origCost, int origAttack, int origDef);

};

#endif
