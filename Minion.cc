#include "Minion.h"
//#include "Enchantment.h"
#include "FireElemental.h"
#include "PotionSeller.h"
#include "NovicePyromancer.h"
#include "ApprenticeSummoner.h"
#include "MasterSummoner.h"
#include "AuraOfPower.h"
#include "StandStill.h"
#include "ActivatedAbilities.h"
#include "TriggeredAbilities.h"
#include "Banish.h"
#include "Blizzard.h"
#include "GiantStrength.h"
#include "MagicFatigue.h"
#include "Silence.h"
#include "Magicless.h"
#include "HealthRestore.h"
#include "Steal.h"
#include "Guardian.h"

using namespace std;

Minion::Minion(string name, string descript, bool owner, int origCost, int origAttack, int origDef)
  : Card{name, "Minion", descript, owner, origCost}, origAttack{origAttack}, origDef{origDef}, currCost{origCost} {
    currAttack = origAttack;
    currDef = origDef; }

//SPELL ATTACKS
bool Minion::receiveSpellFrom(CardPtr c) {
  if (c->getName() == "Banish") {
    cout << "I was here" << endl;
    reset();
    return false;
  }
  return true;
}

void Minion::addMagicless(int i) {
  hasMagicless += i;
}

int Minion::getMagicless(){
  return hasMagicless;
}

vector<EnchantmentPtr> Minion::getEnchantments(){
  return enchants;
}

bool Minion::removeEnchantment() {
  EnchantmentPtr e = enchants[enchants.size()-1];
  if (e->getName() == "Giant Strength") {
    currAttack -= 2;
    currDef -= 2;
    if(currDef <= 0) return false;
  }
  enchants.pop_back();
  return true;
}

bool Minion::receiveAttackFrom(Blizzard &b) {
  currDef -= 2;
  cout << "currDef is " << currDef << endl;
  if (currDef <= 0){
    cout << "Minion died from Blizzard RIPPITY RIP C:" << endl;
    reset(); return false;
  }
  return true;
}

bool Minion::getCanUseAbility() {
  return canUseAbility;
}

void Minion::setCanUseAbility(bool in) {
  canUseAbility = in;
}


bool Minion::receiveAttackFrom(MinionPtr m, bool ability) {
  cout << "ATTACKED" << endl;
  if (ability && m->getCanUseAbility()) {
    string n = m->getName();
    if (n == "Novice Pyromancer") --currDef;
    else if (n == "Fire Elemental") --currDef;
    else if (n == "Potion Seller") ++currDef;
  } else currDef -= m->getCurrAttack();
   if (currDef <= 0){
     cout << "Minion died from" << m->getName() << " RIPPITY RIP C:" << endl;
    reset(); return false;
  }
  return true;
}

void Minion::attachEnchantment(EnchantmentPtr e) {
  enchants.emplace_back(e);
}

//ENCHANTMENT ATTACKS/EFFECTS
void Minion::receiveEnchantFrom(EnchantmentPtr e) {
  if (e->getName() == "Giant Strength") {
    currAttack += 2;
    currDef += 2;
    attachEnchantment(e);
  } else{
    attachEnchantment(e);
  }
}
/*
void Minion::receiveEnchantFrom(GiantStrength &g) {
  currAttack += 2;
  currDef += 2;
  cout << "Received enchant from Giant Strength" << endl;
}

void Minion::receiveEnchantFrom(MagicFatigue &m) {
  currCost += 2;
  cout << "Received enchant from Magic Fatigue" << endl;
}

void Minion::receiveEnchantFrom(Silence &s) {
  canUseAbility = false;
  cout << "received enchant from Silence" << endl;
}
*/
void Minion::attacked(bool reset) {
  if(reset){ hasAttacked = false; return;}
  hasAttacked = true;
}

int Minion::getCurrAttack() {
  return currAttack;
}

void Minion::addCurrAttack(int i){
  currAttack += i;
}

int Minion::getCurrDef(){
  return currDef;
}

void Minion::addCurrDef(int i) {
  currDef += i;
}

bool Minion::getHasAttacked() {
  return hasAttacked;
}

void Minion::reset(){
  currCost = getOrigCost();
  currAttack = origAttack;
  currDef = origDef;

  hasAttacked = false;
  canUseAbility = true;
  enchants.clear();
}

void Minion::displayMinion_helper(int start, int end, vector<card_template_t> &buffer){
  vector<string> row(buffer[0].size());
  for(int i = start; i < end; i++){
    string newRow = "";
    for(int j = 0; j < buffer[i].size(); j++){
      row[j] += buffer[i][j];
    }
  }
  for(int i = 0; i < row.size(); i++){
     cout << row[i] << endl;
  }
}
void Minion::displayMinion(){
  vector<card_template_t> buffer;
  int size = enchants.size();
  
  ActivatedAbilitiesPtr a = dynamic_pointer_cast<ActivatedAbilities>(shared_from_this());
  TriggeredAbilitiesPtr t = dynamic_pointer_cast<TriggeredAbilities>(shared_from_this());;
  card_template_t card;
  if(hasMagicless > 0) {
     card = display_minion_activated_ability(getName(), getOrigCost(), currAttack, currDef, 0, "Decreases opponent's magic by 1");
  }else if(!a && !t){
    card = display_minion_no_ability(getName(), getOrigCost(), currAttack, currDef);
  }else if(a){
    int ability_cost = a->getCurrActCost();
    card = display_minion_activated_ability(getName(), getOrigCost(), currAttack, currDef, ability_cost, getDescription());
  }else if(t){
    card = display_minion_triggered_ability(getName(), getOrigCost(), currAttack, currDef, getDescription());
  }
  for(int i = 0; i < card.size(); i++){
    cout << card[i] << endl;
  }
  for (int i = 0; i < size; i++) {
    string name = enchants[i]->getName();
    int cost = enchants[i]->getOrigCost();
    string descript = enchants[i]->getDescription();
    if (name == "Giant Strength") {
      card_template_t card = display_enchantment_attack_defence(name, cost, descript, "+2", "+2");
      buffer.emplace_back(card);  
    } else {
      card_template_t card = display_enchantment(name, cost, descript);
      buffer.emplace_back(card);  
    }    
  }

  for(int i = 0; i < buffer.size(); i+=5){
    int e = i+5 >= buffer.size() ? buffer.size() : (i+5);
    displayMinion_helper(i, e, buffer);
  }
}

Minion::~Minion(){}
