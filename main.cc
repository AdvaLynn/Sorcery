//main.cc
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>

#include "Owner.h"
#include "GameController.h"
#include "CardFactory.h"


using namespace std;


int main(int argc, char *argv[]) {
  string s;
  cout << "Which file should we read from?  (init)" << endl;

  string name1 = "";
  string name2 = "";

  string deckfile1 = "default.deck";
  string deckfile2 = "default.deck";

  bool testing = false;
  
  vector<string> fileargs;

  //for commandline arguments (set up the game)
  for(int i = 1; i < argc; i++){
    string currArg = argv[i];
    cout << currArg << endl;
    if(currArg  == "-init"){
      i++;
      string filename = argv[i];
      ifstream input{filename};
      string token;
      while(getline(input, token)){
	if(name1 == ""){
          name1 = token;
	}else if(name2 == ""){
          name2 = token;
	}else{
	  fileargs.emplace_back(token);
	}
      }//while
      cout << "name 1 is " << name1 << " name 2 is " << name2 << endl;
    }else if(currArg == "-deck1"){
      i++;
      deckfile1 = i >= argc ? deckfile1 : argv[i];
      cout << "deck1: " << deckfile1 << endl;
    }else if(currArg == "-deck2"){
      i++;
      deckfile2 = i >= argc ? deckfile2 : argv[i];
      cout << "deck2: " << deckfile2 << endl;
    }else if(currArg == "-testing"){
      testing = true;
      cout << "testing: " << testing << endl;
    }
  }//for


  CardFactory cf1{deckfile1, true};
  CardFactory cf2{deckfile2, false};
  vector<CardPtr> o1deck = cf1.makeDeck();
  vector<CardPtr> o2deck = cf2.makeDeck();
  DeckPtr d1 = DeckPtr(new Deck{o1deck, testing});
  DeckPtr d2 = DeckPtr(new Deck{o2deck, testing});

  if(!testing){
    d1->shuffle();
    d2->shuffle();
  }
  
  OwnerPtr o1 = OwnerPtr(new Owner(name1, d1));
  OwnerPtr o2 = OwnerPtr(new Owner(name2, d2));

  GameController gctrl{o1, o2, testing};
  
  gctrl.startGame(fileargs);
} 
