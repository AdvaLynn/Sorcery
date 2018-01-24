#include "CardFactory.h"
#include "AirElemental.h"
#include "EarthElemental.h"
#include "FireElemental.h"
#include "PotionSeller.h"
#include "NovicePyromancer.h"
#include "ApprenticeSummoner.h"
#include "MasterSummoner.h"
#include "Banish.h"
#include "Unsummon.h"
#include "Recharge.h"
#include "Disenchant.h"
#include "RaiseDead.h"
#include "Blizzard.h"
#include "GiantStrength.h"
#include "MagicFatigue.h"
#include "Silence.h"
#include "DarkRitual.h"
#include "AuraOfPower.h"
#include "StandStill.h"
#include "Magicless.h"
#include "HealthRestore.h"
#include "Steal.h"
#include "Guardian.h"

using namespace std;

CardFactory::CardFactory(string name, bool turn)
  : filename{name}, turn{turn}{}

CardPtr CardFactory::makeCard(string n){
  CardPtr c = nullptr;
  if (n == "Air Elemental") {
    c = CardPtr(new AirElemental(turn));
  } else if (n == "Earth Elemental") {
    c = CardPtr(new EarthElemental(turn));
  } else if (n == "Fire Elemental") {
    c = CardPtr(new FireElemental(turn));
  } else if (n == "Potion Seller") {
    c = CardPtr(new PotionSeller(turn));
  } else if (n == "Novice Pyromancer") {
    c = CardPtr(new NovicePyromancer(turn));
  } else if (n == "Apprentice Summoner") {
    c = CardPtr(new ApprenticeSummoner(turn));
  } else if (n == "Master Summoner") {
    c = CardPtr(new MasterSummoner(turn));
  } else if (n == "Banish") {
    c = CardPtr(new Banish(turn));
  } else if (n == "Unsummon") {
    c = CardPtr(new Unsummon(turn));
  } else if (n == "Recharge") {
    c = CardPtr(new Recharge(turn));
  } else if (n == "Disenchant") {
    c = CardPtr(new Disenchant(turn));
  } else if (n == "Raise Dead") {
    c = CardPtr(new RaiseDead(turn));
  } else if (n == "Blizzard") {
    c = CardPtr(new Blizzard(turn));
  } else if (n == "Giant Strength") {
    c = CardPtr(new GiantStrength(turn));
  } else if (n == "Magic Fatigue") {
    c = CardPtr(new MagicFatigue(turn));
  } else if (n == "Silence") {
    c = CardPtr(new Silence(turn));
  } else if (n == "Dark Ritual") {
    c = CardPtr(new DarkRitual(turn));
  } else if (n == "Aura of Power") {
    c = CardPtr(new AuraOfPower(turn));
  } else if (n == "Standstill") {
    c = CardPtr(new StandStill(turn));
  } else if (n == "Magicless") {
    c = CardPtr(new Magicless(turn));
  } else if (n == "Health Restore") {
    c = CardPtr(new HealthRestore(turn));
  } else if (n == "Steal") {
    c = CardPtr(new Steal(turn));
  } else if (n == "Guardian") {
    c = CardPtr(new Guardian(turn));
  }
  return c;
}

vector<CardPtr> CardFactory::makeDeck(){
  ifstream deckfile{filename};
  string cardName;
  vector<CardPtr> deck;
  while(getline(deckfile, cardName)){
    CardPtr c = makeCard(cardName);
    if(c == nullptr){ cout << "no such card " << cardName <<  endl;  continue;}
    deck.emplace_back(c);
  }
  return deck;
}

CardFactory::~CardFactory() {};
