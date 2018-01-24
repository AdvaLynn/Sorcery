#include "Owner.h"

using namespace std;

Owner::Owner (string name, DeckPtr deck)
  : name{name}, magic{3}, health{20}, deck{deck} {}

string Owner::getName() const {
  return name;
}

void Owner::setName(string name){
  this->name = name;
}

void Owner::addMagic(int i){
  magic += i;
}

int Owner::getMagic() {
  return magic;
}

Board &Owner::getBoard(){
  return board;
}

Deck &Owner::getDeck(){
  return *deck;
}

Graveyard &Owner::getGraveyard(){
  return graveyard;
}

Hand &Owner::getHand(){
  return hand;
}
void Owner::draw() {
  if (hand.getCards().size() >= 5){
    cout << "Your hand is full." << endl;
    return;
  }
  if (deck->getCards().size() <= 0){
    cout << "No more cards in deck." << endl;
    return;
  }
  CardPtr c = deck->detach();
  hand.attach(c);
}

void Owner::addHealth(int i) {
  health += i;
}

int Owner::getHealth() {
  return health;
}

void Owner::displayOwner(int p) {
  vector<card_template_t> buffer;
  // RITUAL - OWNER - GRAVEYARD
  RitualPtr r = board.getRitual();
  if(!r){
    buffer.emplace_back(CARD_TEMPLATE_BORDER);
  }else{
    int actCost = r->getCurrActCost();
    int charge = r->getCurrCharge();
    card_template_t ritualCard = display_ritual(r->getName(), r->getOrigCost(), actCost, r->getDescription(), charge);
    buffer.emplace_back(ritualCard);
  }
  buffer.emplace_back(CARD_TEMPLATE_EMPTY);
  card_template_t ownerCard = display_player_card(p, name, health, magic);
  buffer.emplace_back(ownerCard);
  buffer.emplace_back(CARD_TEMPLATE_EMPTY);

  if (graveyard.getMinions().size() <= 0) {
    buffer.emplace_back(CARD_TEMPLATE_BORDER);
  }else{
    MinionPtr m = graveyard.getMinions()[graveyard.getMinions().size()-1];
    string minName = m->getName();
    int cost = m->getOrigCost();
    string descript = m->getDescription();
    ActivatedAbilitiesPtr a = dynamic_pointer_cast<ActivatedAbilities>(m);
    TriggeredAbilitiesPtr t = dynamic_pointer_cast<TriggeredAbilities>(m);
    int attack = m->getCurrAttack();
    int defence = m->getCurrDef();
    if(!a && !t){
      card_template_t card = display_minion_no_ability(minName, cost, attack, defence);
      buffer.emplace_back(card);
    }else if(a){
      int ability_cost = a->getCurrActCost();
      card_template_t card = display_minion_activated_ability(minName, cost, attack, defence, ability_cost, descript);
      buffer.emplace_back(card);
    }else if(t){
      card_template_t card = display_minion_triggered_ability(minName, cost, attack, defence, descript);
      buffer.emplace_back(card);
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

  displayBorder(p, row);
}

void Owner::displayBorder(int p, vector<string> &row) {
  if(p == 1){
    string corner_left = EXTERNAL_BORDER_CHAR_TOP_LEFT;
    string corner_right = EXTERNAL_BORDER_CHAR_TOP_RIGHT;
    
    int length = 164;
    cout << corner_left;
    for(int i = 0; i <= length; i++){
      cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << corner_right << endl;
    for(int i = 0; i < row.size(); i++){
      cout << row[i] << endl;
    }
  }else if (p == 2){
    for(int i = 0; i < row.size(); i++){
      cout << row[i] << endl;
    }
    string corner_left = EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    string corner_right = EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT;
    
    cout << corner_left;
    int length = 164;
    for(int i = 0; i <= length; i++){
      cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << corner_right << endl;
  }
}

Owner::~Owner(){}
