#include "Board.h"
/*
#include "Ritual.h"
#include "ascii_graphics.h"
#include "ActivatedAbilities.h"
#include "TriggeredAbilities.h"
#include "Spell.h"
#include "Ritual.h"
#include "Enchantment.h"
*/

using namespace std;

Board::Board() : ritual{nullptr} {}

Board::~Board() {}

void Board::attach(MinionPtr m){
  cout << "Summon Minion " << m->getName() << endl;
  minions.emplace_back(m);
}

void Board::detach(MinionPtr m){
  int size = minions.size();
  for (int i = 0; i < size; ++i) {
    if (minions[i] == m) {
      minions.erase(minions.begin() + i);
      break;
    }
  }
  cout << "Minion " << m->getName() << " leaves Board. " << endl;
}

vector<MinionPtr> &Board::getMinions(){
  return minions;
}

RitualPtr Board::getRitual() {
  return ritual;
}

void Board::displayBoard() {
  vector<card_template_t> buffer;
  int size = minions.size();
  for (int i = 0; i < size; i++) {
    string type = minions[i]->getType();
    string name = minions[i]->getName();
    int cost = minions[i]->getOrigCost();
    string descript = minions[i]->getDescription();
    if(type == "Spell"){
      card_template_t card = display_spell(name, cost, descript);
      buffer.emplace_back(card);
    }else if(type == "Ritual"){
      RitualPtr r = dynamic_pointer_cast<Ritual>(minions[i]);
      int actCost = r->getCurrActCost();
      int charge = r->getCurrCharge();
      card_template_t card = display_ritual(name, cost, actCost, descript, charge);
      buffer.emplace_back(card);
    }else if(type  == "Enchantment"){
      card_template_t card = display_enchantment(name, cost, descript);
      buffer.emplace_back(card);
    }else if(type == "Minion"){
      ActivatedAbilitiesPtr a = dynamic_pointer_cast<ActivatedAbilities>(minions[i]);
      TriggeredAbilitiesPtr t = dynamic_pointer_cast<TriggeredAbilities>(minions[i]);
      MinionPtr m = dynamic_pointer_cast<Minion>(minions[i]);
      int attack = m->getCurrAttack();
      int defence = m->getCurrDef();
      if(m->getMagicless() > 0) {
	card_template_t card = display_minion_activated_ability(name, cost, attack, defence, 0, "Decreases opponent's magic by 1");
	buffer.emplace_back(card);
      }else if(!a && !t){
	card_template_t card = display_minion_no_ability(name, cost, attack, defence);
	buffer.emplace_back(card);
      }else if(a){
	int ability_cost = a->getCurrActCost();
	card_template_t card = display_minion_activated_ability(name, cost, attack, defence, ability_cost, descript);
	buffer.emplace_back(card);
      }else if(t){
	card_template_t card = display_minion_triggered_ability(name, cost, attack, defence, descript);
	buffer.emplace_back(card);
      }
    }
  }
  if (size < 5) {
    for (int i = 0; i < (5-size); ++i) {
      buffer.emplace_back(CARD_TEMPLATE_BORDER);
    }
  }
  vector<string> row(buffer[0].size());
    
  for(int i = 0; i < row.size(); i++){
    row[i] += EXTERNAL_BORDER_CHAR_UP_DOWN;
  }
  
  for(int i = 0; i < buffer.size(); i++){
    string newRow = "";
    for(int j = 0; j < buffer[i].size(); j++){
      row[j] += buffer[i][j];
    }
  }
    
  for(int i = 0; i < row.size(); i++){
    row[i] += EXTERNAL_BORDER_CHAR_UP_DOWN;
  }
  
  for(int i = 0; i < row.size(); i++){
    cout << row[i] << endl;
  }
}

void Board::setRitual(RitualPtr r) {
  ritual = r;
}
