#include "Deck.h"

using namespace std;

//Shuffles the current deck. 
void Deck::shuffle () {
  random_shuffle(deckCards.begin(), deckCards.end());
//  cout << "shuffled deck is now: " << endl;
  /*for(int i = 0; i < deckCards.size(); i++){
    cout << deckCards[i]->getName() << endl;
    }*/
  return;
}


Deck::Deck(vector<CardPtr> deckCards, bool testing)
  : deckCards{deckCards}, testing{testing} {
    cout << "constructing deck ..." << endl;
}

vector<CardPtr> Deck::getCards() {
  return deckCards;
}

void Deck::attach(CardPtr c) {
  deckCards.emplace_back(c);
}

CardPtr Deck::detach() {
  CardPtr result = deckCards[0];
  reverse(deckCards.begin(), deckCards.end());
  deckCards.pop_back();
  reverse(deckCards.begin(), deckCards.end());
  return result;
}

Deck::~Deck(){}
