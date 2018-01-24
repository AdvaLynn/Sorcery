#ifndef CARD_H
#define CARD_H
#include <memory>
#include <string>

class Card;
typedef std::shared_ptr<Card> CardPtr;

class Card : public std::enable_shared_from_this<Card> {
  const std::string type;
  const std::string name;
  const std::string descript;
  bool owner;
  const int origCost;

 public:

  std::string getType() const;
  std::string getName() const;
  bool getOwner();
  void toggleOwner();
  int getOrigCost() const;
  std::string getDescription() const;
  virtual ~Card();
  
 protected:
  Card(std::string name, std::string type, std::string descript, bool owner, int origCost);
};

#endif
