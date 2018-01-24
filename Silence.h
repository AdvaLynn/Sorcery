#ifndef SILENCE_H
#define SILENCE_H
#include <iostream>
#include <memory>
#include <string>
#include "Enchantment.h"

class Silence;
typedef std::shared_ptr<Silence> SilencePtr;

class Silence : public Enchantment {
 public:
  Silence(bool owner);
  ~Silence();
};

#endif

