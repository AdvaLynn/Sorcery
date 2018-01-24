#include "Hand.h"
/*
#include "Card.h"
#include "Minion.h"
#include "ActivatedAbilities.h"
#include "TriggeredAbilities.h"
#include "Spell.h"
#include "Enchantment.h"
#include "Ritual.h"
#include "ascii_graphics.h"
*/

using namespace std;

Hand::Hand (){}

//Returns cards vector (the current cards in Hand)
vector<CardPtr> Hand::getCards() {
  return cards;
}

void Hand::attach(CardPtr c) {
  cards.emplace_back(c);
}

CardPtr Hand::detach(int i) {
  if(i < 0 || i >= cards.size()) {cout << "Please enter valid index." << endl; return CardPtr{nullptr};}
  CardPtr result = cards[i];
  cards.erase(cards.begin() + i);
  return result;
}
void Hand::displayHand() {
  vector<card_template_t> buffer;
  int size = cards.size();
  if (size <= 0) {
    cout << endl;
    return;
  }
  for (int i = 0; i < size; i++) {
    string type = cards[i]->getType();
    string name = cards[i]->getName();
    int cost = cards[i]->getOrigCost();
    string descript = cards[i]->getDescription();
    if(type == "Spell"){
      card_template_t card = display_spell(name, cost, descript);
      buffer.emplace_back(card);
    }else if(type == "Ritual"){
      RitualPtr r = dynamic_pointer_cast<Ritual> (cards[i]);
      int actCost = r->getCurrActCost();
      int charge = r->getCurrCharge();
      card_template_t card = display_ritual(name, cost, actCost, descript, charge);
      buffer.emplace_back(card);
    }else if(type  == "Enchantment"){
      if(name == "Giant Strength"){
	card_template_t card = display_enchantment_attack_defence(name, cost, descript, "+2", "+2");
	buffer.emplace_back(card);
      }else{
	card_template_t card = display_enchantment(name, cost, descript);
	buffer.emplace_back(card);
      }
    }else if(type == "Minion"){
      ActivatedAbilitiesPtr a = dynamic_pointer_cast<ActivatedAbilities>(cards[i]);
      TriggeredAbilitiesPtr t = dynamic_pointer_cast<TriggeredAbilities>(cards[i]);
      MinionPtr m = dynamic_pointer_cast<Minion>(cards[i]);
      int attack = m->getCurrAttack();
      int defence = m->getCurrDef();
      if(!a && !t){
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
  vector<string> row(buffer[0].size());
  for(int i = 0; i < buffer.size(); i++){
    string newRow = "";
    for(int j = 0; j < buffer[i].size(); j++){
      row[j] += buffer[i][j];
    }
  }
  for(int i = 0; i < row.size(); i++){
    cout << row[i] << endl;
  }
}

//Dtor
Hand::~Hand(){}
