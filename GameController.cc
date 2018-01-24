#include "GameController.h"
#include "Card.h"
using namespace std;

// CONSTRUCTOR //
GameController::GameController(OwnerPtr o1, OwnerPtr o2, bool testing)
  : o1{o1}, o2{o2}, testing{testing}{}

/*
  ===============================================
  USEFUL GAMECTRLER METHODS
  ===============================================
*/

//fetch(OwnerPtr o, int i): fetches a shared Minion pointer from board based on index i.
MinionPtr GameController::fetch(OwnerPtr o, int i) {
  if (i >= o->getBoard().getMinions().size() || i < 0) {
    cerr << "Cannot fetch minion. Please enter valid index" << endl;
    return nullptr;
  }
  return o->getBoard().getMinions()[i];
}

//fetchHand(OwnerPtr o, int i): fetches a shared Card pointer from hand based on index i.
CardPtr GameController::fetchHand(OwnerPtr o, int i) {
  vector <CardPtr> cv = o->getHand().getCards();
  if (i >= cv.size() || i < 0) {
    cerr << "Cannot fetch card. Please enter valid index" << endl;
    return nullptr;
  }
  return o->getHand().getCards()[i];
}

//reset(): resets whether minion has attacked.
void GameController::reset() {
  for (int i = 0; i < getAP()->getBoard().getMinions().size(); i++) {
    getAP()->getBoard().getMinions()[i]->attacked(true);
  }
}

//bury(MinionPtr m): moves a minion from Board to Graveyard.
void GameController::bury(MinionPtr m) {
  OwnerPtr o = m->getOwner() ? o1 : o2;
  m->reset();
  o->getGraveyard().attach(m);
  o->getBoard().detach(m);
cout << m->getName() << " has died." << endl;
  int i = o1->getGraveyard().getMinions().size();
  int j = o1->getBoard().getMinions().size();
  RitualPtr r = o->getBoard().getRitual();
  if(!r) return;
  if(r->getName() == "Health Restore"){
    if(r->getCurrCharge() < r->getCurrActCost()) return;
    r->charge(-1);
    o->addHealth(1);
  }
}

//getAP(): gets the active player
OwnerPtr GameController::getAP() {
  if (turn) return o1;
  return o2;
}

//getNAP(): gets the non active player
OwnerPtr GameController::getNAP() {
  if (turn) return o2;
  return o1;
}

//summon(int num, MinionPtr summoned): summon "min([board-empty-spots], num)" amount of Minions of type summoned.
bool GameController::summon(int num, MinionPtr summoned) {
  Board &b = getAP()->getBoard();
  int res = (5 - b.getMinions().size()) < num ? (5 - b.getMinions().size()) : num;
  if (res == 0) return false;
  b.attach(summoned);
  triggerAuraOfPower();
  bool triggered = triggerStandstill();
  if(!triggered) triggerFireElemental();
  for (int i = 0; i < res-1; ++i) {
    AirElementalPtr a = AirElementalPtr(new AirElemental(turn));
    b.attach(a);
    triggerAuraOfPower();
    bool triggered = triggerStandstill();
    if(!triggered) triggerFireElemental();
  }
  return true;
}

//unsummon(MinionPtr m, OwnerPtr o): moves Minion m from board back to Owner o's deck.
void GameController::unsummon(MinionPtr m, OwnerPtr o) {
  o->getBoard().detach(m);
  o->getDeck().attach(m);
cout << m->getName() << " has been unsummoned." << endl;
}

//triggerPotionSeller(): triggers PotionSelller's ability.
void GameController::triggerPotionSeller(){
  bool exists = false;
  vector<MinionPtr> cards = getAP()->getBoard().getMinions();
  int size = cards.size();
  for(int i = 0; i < size; i++) {
    if(cards[i]->getName() == "Potion Seller"){
      exists = true;
      break;
    }
  }
  if(exists){
    for(int i = 0; i < size; i++){
      cards[i]->addCurrDef(1);
      cout << cards[i]->getName() << " gains +1 defence from Potion Seller." << endl;
    }
  }
}

//triggerDarkRitual(): triggers DarkRitual's ability.
void GameController::triggerDarkRitual(){
  RitualPtr r = getAP()->getBoard().getRitual();
  if (!r) return;
  if (r->getCurrCharge() <= 0) return;
  if (r && r->getName() == "Dark Ritual") {
    getAP()->addMagic(1);
    cout << getAP()->getName() << " gains +1 magic from Dark Ritual." << endl; 
    // add decrease in charge
    r->charge(-1);
  }
}

//displaySorcery(): displays the center graphics.
void GameController::displaySorcery() {
  for(int i = 0; i < CENTRE_GRAPHIC.size(); i++){
    cout << CENTRE_GRAPHIC[i] << endl;
  }
}

//printHelp(): prints message from -help command.
void GameController::printHelp(){
  cout << "Commands: help -- Display this message." << endl;
  cout << "          end -- End the current players turn." << endl;
  cout << "          quit -- End the game." << endl;
  cout << "          attack minion other --Orders minion to attack other-minion." << endl;
  cout << "          attack minion -- Orders minion to attack the opponent." << endl;
  cout << "          play card [target-player target-card] == Play card, optionally targeting target-card owned by target-player." << endl;
  cout << "          use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << endl; 
  cout << "          inspect minion -- View a minion's card and all enchantments on that minion." << endl;
  cout << "          hand -- Describe all cards in your hand." << endl;
  cout << "          board -- Describe all cards on the board." << endl;
}

/*
  ========================================
  GAME LOOP STARTS
  ========================================
*/

//startGame(vector<string> fileargs): main game loop
void GameController::startGame(vector<string> fileargs) {

  string name1, name2;
   //LOAD HAND FOR BOTH PLAYERS
  for (int i = 0; i < 4; i++) {
    getAP()->draw();
    getNAP()->draw();
  }
  //INITIALIZING FROM FILE//
  int size = fileargs.size();
  for (int i = 0; i < size; ++i) {
    startGame_helper(fileargs[i]);
    if(draw == 0){ cout << "GAME OVER" << endl; return; }
  }
  //GET PLAYERS NAMES//
  if (o1->getName() == "") {
    cout << "What is the first player's name?" <<endl;
    cin >> name1;
    cout << "player1's name is " << name1 << endl;
    o1->setName(name1);
  }
  if (o2->getName() == "") {
    cout << "What is the second player's name?" <<endl;
    cin >> name2;
    cout << "player2's name is " << name2 << endl;
    o2->setName(name2);
  }
 
  //STARTS GAME
  string cmd;
  while(getline(cin, cmd)){
    startGame_helper(cmd);
    if(draw == 0) break;
  }
  //ENDS GAME
  cout << "GAME OVER" << endl;
}

void GameController::startGame_helper(string cmd) {
  istringstream iss{cmd};
  string currcmd;
  while(iss >> currcmd){
    
    if (currcmd == "help") {
      printHelp();
    } else if (currcmd == "end") {
      triggerPotionSeller();
      reset();
      turn = !turn;
      triggerDarkRitual();
      getAP()->draw();
      getAP()->addMagic(1);
      
      //display board
      o1->displayOwner(1);
      o1->getBoard().displayBoard();
      displaySorcery();
      o2->getBoard().displayBoard();
      o2->displayOwner(2);
      //
      cout << "It is " << getAP()->getName() << "'s turn now." << endl;
    } else if (currcmd == "quit") {
      draw = 0;
      break;
    } else if (currcmd == "draw") {
      if (!testing) continue;
      getAP()->draw();
    } else if (currcmd == "discard") {
      if (!testing) continue;
      int cardNum = -1;
      iss >> cardNum;
      if(iss.fail()){
	cerr << "Please enter a valid index" << endl;
	continue;
      }
      --cardNum;
      CardPtr c = getAP()->getHand().detach(cardNum);
    } else if (currcmd == "attack") {
      int arg1, arg2 = -1;
      iss >> arg1;
      if(iss.fail()){
	cerr << "Please enter a valid index" << endl;
	continue;
      }
      iss >> arg2;
      if(iss.fail()){
	Attack(arg1);
	//PLAYER HAS DIED RIP
	if(getNAP()->getHealth() <= 0){
	  cout << getAP()->getName() << " has won! " << endl;
	  draw = 0;
	  break;
	}
      }else{
	Attack(arg1, arg2);
      }
    } else if (currcmd == "play") {
      int arg1, arg2;
      string arg3;
      iss >> arg1;
      if(iss.fail()) {
	cerr << "Please enter valid command argument " << endl;
	continue;
      }
      iss >> arg2; iss >> arg3;
      if(iss.fail()) {
	Play(arg1);
      }else{
	Play(arg1, arg2, arg3);
      }
    } else if (currcmd == "use") {
      int  arg1, arg2, arg3 = -1;
      iss >> arg1;
      if (iss.fail()) {
	cerr << "Please enter valid command argument." << endl;
	continue;
      }
      iss >> arg2; iss >> arg3;
      if (iss.fail()){ 
	Use(arg1);
      } else {
	Use(arg1, arg2, arg3);
      }
    } else if (currcmd == "inspect") {
      int arg;
      iss >> arg;
      if (iss.fail()){ cout << "Please enter valid index." << endl; continue;}
      --arg;
      vector <MinionPtr> minions = getAP()->getBoard().getMinions();

      //ERROR CHECKING
      if(arg < 0 || arg >= minions.size() ){
	cout << "Please enter a valid index to inspect minion" << endl;
      }
      //
      
      getAP()->getBoard().getMinions()[arg]->displayMinion();
    } else if (currcmd == "hand") {
      int s = getAP()->getHand().getCards().size();
      getAP()->getHand().displayHand();
    } else if (currcmd == "board") {
      //display board
      o1->displayOwner(1);
      o1->getBoard().displayBoard();
      displaySorcery();
      o2->getBoard().displayBoard();
      o2->displayOwner(2);
    }
  }
}


/*
  =========================================
  USE COMMAND
  =========================================
*/

//Use(int i, int p, int j): Use Minion i's ability on Player p's Minion j. 
void GameController::Use(int i, int p, int j) {
  --i;
  --j;
  OwnerPtr o = nullptr;

  // ERROR CHECKING
  if(p == 1) o = o1;
  else if(p == 2) o = o2;
  else {
    cout << "Invalid Player index entered." << endl;
    return;
  }

  vector <MinionPtr> board1 = getAP()->getBoard().getMinions();
  vector <MinionPtr> board2 = o->getBoard().getMinions();
  if(i < 0 || i >= board1.size() || j < 0 || j >= board2.size()){
    cout << "Invalid mininon selected." << endl;
    return;
  }
  //
  
  MinionPtr m1 = fetch(getAP(), i);
  vector<EnchantmentPtr> enchants = m1->getEnchantments();

  // CHECK FOR WHETHER MINION CAN USE ABILITY
  bool canUseAbility = true;
  for(int i = enchants.size()-1; i >=0; i--){
    if(enchants[i]->getName() == "Magicless") break;
    if(enchants[i]->getName() == "Silence"){
      canUseAbility = false;
      break;
    }
  }
  if(!canUseAbility){
    cout << "Minion cannot use/does not have activated ability." << endl; 
  } 
  //
  
  // CHECK FOR WHETHER MINION HAS ACTIVATED ABILITY
  ActivatedAbilitiesPtr a = dynamic_pointer_cast<ActivatedAbilities>(m1);
  if(!a){cout <<  "Minion " << m1->getName() << " has no activated abilities." << endl; return; }
  int amt = 0;
  int difference = getAP()->getMagic()-a->getOrigCost();
  if (!testing){
    if(difference < 0){ cout << "You don't have enough magic to play this card." << endl; return; }
    amt = -a->getOrigCost();
  }else{
    amt = difference <= 0 ? -1*getAP()->getMagic() : -1*a->getOrigCost();
  }
  //

  // CHECK FOR WHETHER MINION HAS ATTACKED
  if (a->getHasAttacked()) return;
  //

  MinionPtr m2 = fetch(o, j);
  
  if(a->getName() != "Novice Pyromancer"){
    cerr << "Cannot use " << a->getName() << " on " << m2->getName() << "."  << endl;
    return;
  }
  
cout << m1->getName() << " has used its activated ability on " << o->getName() << "'s " << m2->getName() << "." << endl;
  
  bool alive = m2->receiveAttackFrom(a, true);
  getAP()->addMagic(amt);
  a->attacked();
  if(!alive){
    bury(m2);
  }
}

//Use(int i): Uses Active Player's Minion i's ability
void GameController::Use(int i) {
  --i;
  
  // ERROR CHECKING
  vector <MinionPtr> board1 = getAP()->getBoard().getMinions();
  if(i < 0 || i >= board1.size()){
    cout << "Invalid mininon selected." << endl;
    return;
  }
  //
  
  MinionPtr m = fetch(getAP(), i);
  ActivatedAbilitiesPtr a = dynamic_pointer_cast<ActivatedAbilities>(m);
  // CHECK IF MINION CAN USE ABILITY
  vector<EnchantmentPtr> enchants = m->getEnchantments();
  bool canUseAbility = true;
  for(int i = enchants.size()-1; i >=0; i--){
    if(enchants[i]->getName() == "Magicless") break;
    if(enchants[i]->getName() == "Silence"){
      canUseAbility = false;
      break;
    }
  }

  if( m->getHasAttacked() || !canUseAbility){
    cout << "Minion cannot use ability." << endl;
    return;
  }
  //

  if(m->getMagicless() > 0){
cout << m->getName() << " has used Magicless on " << getNAP()->getName() << "." << endl;
    m->attacked();
    getNAP()->addMagic(-1);
    return;
  }
 
  //CEHCK FOR WHETER CAN USE ACTIVATED ABILITIES
  if(!a){cout <<  "Minion " << m->getName() << " has no activated abilities." << endl; return; }  
  //

  int amt = 0;
  int difference = getAP()->getMagic()-a->getCurrActCost();
  if (!testing){
    if(difference < 0){ cout << "You don't have enough magic to play this card." << endl; return; }
    amt = -a->getCurrActCost();
  }else{
    amt = difference <= 0 ? -1*getAP()->getMagic() : -1*a->getCurrActCost();
  }
  cout << "Name is " << m->getName() << endl;
  if (m->getHasAttacked()) return;
  if ((m->getName() != "Apprentice Summoner") && (m->getName() != "Master Summoner")){
    cerr << "Invalid Card" << endl;
    return;
  }
  int num =  m->getName() == "Master Summoner" ? 3 : 1;
  getAP()->addMagic(amt);
  AirElementalPtr air = AirElementalPtr(new AirElemental(turn));
  bool res = summon(num, air);
  if(res){
    m->attacked();
  }else {
    cout << "Your board is full. Cannot summon anymore Air Elementals." << endl;
  }
}

//triggerFireElemental(): triggers Fire Elemental's ability
void GameController::triggerFireElemental() {
  bool exists = false;
  vector <MinionPtr> cards1 = getNAP()->getBoard().getMinions();
  vector <MinionPtr> cards2 = getAP()->getBoard().getMinions();
  int size = cards1.size();
  for (int i = 0; i < size; i++) {
    if (cards1[i]->getName() == "Fire Elemental") {
      exists = true;
      break;
    }
  }
  if (exists) {
    cards2[cards2.size()-1]->addCurrDef(-1);
    if (cards2[cards2.size()-1]->getCurrDef() <= 0) {
      bury(cards2[cards2.size()-1]);
    }
  }  
}

//triggerAuraOfPower(): triggers AuraOfPower's Ability
void GameController::triggerAuraOfPower() {
  RitualPtr r = getAP()->getBoard().getRitual();
  if(!r) return;
  if (r->getCurrCharge() <= 0) return;
  if (r && r->getName() == "Aura of Power") {
    vector <MinionPtr> c = getAP()->getBoard().getMinions();
    c[c.size()-1]->addCurrDef(1);
    c[c.size()-1]->addCurrAttack(1);
    r->charge(-1);
  }
}

//triggerStandStill(): triggers Standstill's ability
bool GameController::triggerStandstill() {
  RitualPtr r1 = getAP()->getBoard().getRitual();
  RitualPtr r2 = getNAP()->getBoard().getRitual();
  vector <MinionPtr> minions = getAP()->getBoard().getMinions();
  MinionPtr m = minions[minions.size()-1];
  if (r1 && r1->getName() == "Standstill"){
    if(r1->getCurrCharge() < 2) return false;
    bury(m);
    r1->charge(-2);
    return true;
  }
  if (r2 && r2->getName() == "Standstill"){
    if(r2->getCurrCharge() < 2) return false;
    bury(m);
    r2->charge(-2);
    return true;
  }
  return false;
}

/*
  ==========================================
  PLAY COMMANDS
  ==========================================
*/

//playBlizzard(): plays Blizzard
void GameController::playBlizzard() {
  int size1 = getAP()->getBoard().getMinions().size();
  int size2 = getNAP()->getBoard().getMinions().size();
  BlizzardPtr b = BlizzardPtr(new Blizzard(true));
  for (int i = 0; i < size1; i++) {
    fetch(getAP(),i)->receiveAttackFrom(*b);
  }
  for (int i = 0; i < size2; i++) {
    fetch(getNAP(),i)->receiveAttackFrom(*b);
  }
}

//playRecharge(): plays Recharge
void GameController::playRecharge() {
  getAP()->getBoard().getRitual()->charge(3);
}

//playRaiseDead(): plays Raise Dead
void GameController::playRaiseDead() {
  MinionPtr m = getAP()->getGraveyard().detach();
  getAP()->getBoard().attach(m);
  triggerAuraOfPower();
  bool triggered = triggerStandstill();
  if(!triggered) triggerFireElemental();
}

//Play(int i): plays Card i in active player's hand
void GameController::Play(int i) {
  --i;
  int size = getAP()->getHand().getCards().size();
  
  //ERROR CHECKING
  if (i >= size || i < 0) {
    cout << "Invalid index chosen. Please play again." << endl;
    return;
  }
  //
  
  CardPtr c = fetchHand(getAP(), i);
  int amt = 0;
  int difference = getAP()->getMagic()-c->getOrigCost();
  if (!testing){
    if(difference < 0){ cout << "You don't have enough magic to play this card." << endl; return; }
    amt = -c->getOrigCost();
  }else{
    amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c->getOrigCost();
  }

cout << getAP()->getName() << " has played " << c->getName() << "." << endl;

  if (c->getType() == "Spell") {
    string name = c->getName();
    if (name == "Recharge" && getAP()->getBoard().getRitual()){
      playRecharge();
      CardPtr spell = getAP()->getHand().detach(i);
    } else if (name == "Raise Dead" && getAP()->getGraveyard().getMinions().size() > 0){
      playRaiseDead();
      CardPtr spell = getAP()->getHand().detach(i);
    }else if (name == "Blizzard"){
      playBlizzard();
      CardPtr spell = getAP()->getHand().detach(i);
    }else if (name == "Steal"){
      int size = getNAP()->getHand().getCards().size();
      if (size <= 0) return;
      CardPtr spell = getAP()->getHand().detach(i);
      int stolenCardIndex = rand()%size;
      CardPtr stolen =  getNAP()->getHand().detach(stolenCardIndex);
      stolen->toggleOwner();
      getAP()->getHand().attach(stolen);
    }else cout << "Cannot play card.!" << endl;
  }else if (c->getType() == "Minion"){
    int size = getAP()->getBoard().getMinions().size();
    if(size >= 5){cout << "Board is Full" << endl; return;}
    CardPtr m = getAP()->getHand().detach(i);
    MinionPtr min = dynamic_pointer_cast<Minion>(m);
    getAP()->getBoard().attach(min);
    triggerAuraOfPower();
    bool triggered = triggerStandstill();
    if(!triggered) triggerFireElemental();
  }else if (c->getType() == "Ritual"){
    RitualPtr r = dynamic_pointer_cast<Ritual>(c);
    getAP()->getBoard().setRitual(r);
    getAP()->getHand().detach(i);
  }else{
    cout << "Cannot play card." << endl;
  }
  getAP()->addMagic(amt);
}

//Play(int i, int p, string j): plays the ith's card in active player's hand on player p's minion j or ritual r.
void GameController::Play(int i, int p, string j) {
  --i;
  int size = getAP()->getHand().getCards().size();
  if (i >= size || i < 0) {
    cout << "Invalid index chosen, cannot play card. Please play again." << endl;
    return;
  }
  CardPtr c1 = fetchHand(getAP(), i);
  OwnerPtr o = p == 1 ? o1 : o2;
  int num;
  istringstream iss{j};

  // J is a ritual
  if((j == "r") && c1->getName() == "Recharge") {
    RitualPtr r = o->getBoard().getRitual();
    if(!r) return;
    int amt = 0;
    if(!testing){
      if(getAP()->getMagic() < c1->getOrigCost()){ cout << "You don't have enough magic to play this card." << endl; return; }
      amt = -1*c1->getOrigCost();
    }else{
      int difference = getAP()->getMagic()-c1->getOrigCost();
      amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c1->getOrigCost();
    }
    r->charge(3);
    getAP()->addMagic(-1*c1->getOrigCost());
    CardPtr spell = getAP()->getHand().detach(i);
  }else if((j == "r") && c1->getName() == "Banish") {
    RitualPtr r = o->getBoard().getRitual();
    if(!r) return;
    o->getBoard().setRitual(nullptr);
    CardPtr spell = getAP()->getHand().detach(i);
  }else if (iss >> num){
    --num;
    int size = o->getBoard().getMinions().size();
    if (num >= size || num < 0) {
      cout << "Invalid index chosen, cannot play card. Please play again." << endl;
      return;
    }
    MinionPtr m = fetch(o, num);
    if(c1->getType() == "Enchantment"){
      int amt = 0;
      if (!testing) {	
	if(getAP()->getMagic() < c1->getOrigCost()){ cout << "You don't have enough magic to play this card." << endl; return; }
	amt = -1*c1->getOrigCost();
      }else{
        int difference = getAP()->getMagic()-c1->getOrigCost();
        amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c1->getOrigCost();
      }
      ActivatedAbilitiesPtr a = dynamic_pointer_cast<ActivatedAbilities>(m);
      EnchantmentPtr e = dynamic_pointer_cast<Enchantment>(c1);
      if(!a){
	m->receiveEnchantFrom(e);
      }else{
	a->receiveEnchantFrom(e);
      }
      if(c1->getName() == "Magicless"){
	m->addMagicless(1);
      }
      getAP()->addMagic(amt);
      getAP()->getHand().detach(i);
    }else if(c1->getType() == "Spell"){
	  if(c1->getName() == "Unsummon") {
	    int amt = 0;
	    if (!testing) {
	      if(getAP()->getMagic() < 1){ cout << "You don't have enough magic to play this card." << endl; return;}
	      amt = -1*c1->getOrigCost();
	    }
	    else {
	      int difference = getAP()->getMagic()-c1->getOrigCost();
	      amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c1->getOrigCost();
	    }
	    unsummon(m,o);
	    getAP()->addMagic(amt);
	    CardPtr spell = getAP()->getHand().detach(i);
	  }else if(c1->getName() == "Banish") {
	    int amt = 0;
	    if (!testing) {
	      if(getAP()->getMagic() < 1){ cout << "You don't have enough magic to play this card." << endl; return; }
	      amt = -1*c1->getOrigCost();
	    }
	    else {
	      int difference = getAP()->getMagic()-c1->getOrigCost();
	      amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c1->getOrigCost();
	    }
	    m->receiveSpellFrom(c1);
	    bury(m);
	    getAP()->addMagic(amt);
	    CardPtr spell = getAP()->getHand().detach(i);
	  }else if(c1->getName() == "Disenchant") {
	    int amt = 0;
	    if(m->enchants.size() == 0){
	      cout << "Cannot play Disenchant on minion without enchantments." << endl;
	      return;
	    }
	    if (!testing) {
	      if(getAP()->getMagic() < 1){ cout << "You don't have enough magic to play this card." << endl; return; }
	      amt = -1*c1->getOrigCost();
	    }else {
	      int difference = getAP()->getMagic()-c1->getOrigCost();
	      amt = difference <= 0 ? -1*getAP()->getMagic() : -1*c1->getOrigCost();
	    }
	    ActivatedAbilitiesPtr a = dynamic_pointer_cast<ActivatedAbilities>(m);
	    if(m->enchants.size() > 0 && m->enchants[m->enchants.size()-1]->getName() == "Magicless"){
	      m->addMagicless(-1);
	    }
	    bool alive = true;
	    if (a) {
	      alive = a->removeEnchantment();
	    } else {
	      alive = m->removeEnchantment();
	    }
            if(!alive){
	      bury(m);
            }
	    amt = -1*c1->getOrigCost() <= 0 ? 0 : -1*c1->getOrigCost();
	    getAP()->addMagic(amt);
	    CardPtr spell = getAP()->getHand().detach(i);
	  }
	}
  }//spell
}//ISS

  /*
    ==========================================
    ATTACK COMMANDS
    ==========================================
  */

//Attack(int i, int j): active player's minion i attacks non active player's minion j and vice versa
void GameController::Attack(int i, int j) {
  --i;
  --j;

  //ERROR CHECKING
  int size1 = getAP()->getBoard().getMinions().size();
  int size2 = getNAP()->getBoard().getMinions().size();
  if (i >= size1 || i < 0 || j >= size2 || j < 0) {
    cout << "Invalid index chosen, cannot attack minion. Please try again." << endl;
    return;
  }
  //
  
  MinionPtr m1 = fetch(getAP(), i);
  MinionPtr m2 = fetch(getNAP(), j);
  if (m1->getHasAttacked()){ cout << "Minion has already attacked." << endl; return;}
  bool alive1= (m1->receiveAttackFrom(m2, false));
  bool alive2= (m2->receiveAttackFrom(m1, false));
  m1->attacked();
  if (!alive1) bury(m1);
  if (!alive2) bury(m2);
}

//Attack(int i): active player's minion i attacks owner
void GameController::Attack(int i) {
  --i;
  int size = getAP()->getBoard().getMinions().size();

  //ERROR CHECKING
  if (i >= size || i < 0) {
    cout << "Invalid index chosen, cannot attack owner. Please try again." << endl;
    return;
  }
  //
  vector<MinionPtr> mins = getNAP()->getBoard().getMinions();
  int existGuard = -1;
  for (int i = 0; i < mins.size(); i++){
    if(mins[i]->getName() == "Guardian"){
      existGuard = i;
      break;
    }
  }
  MinionPtr c = fetch(getAP(), i);

  if (c->getHasAttacked()) { cout << "Minion has attacked" << endl; return; }
  if(existGuard >= 0 && c->getMagicless() == 0){
    Attack(i, existGuard);
  }else{
    int n = c->getCurrAttack();
    getNAP()->addHealth(-n);
    c->attacked();
cout << c->getName() << " has attacked " << getNAP()->getName() << "." << endl;
  }
  
}
 
