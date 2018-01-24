#ifndef NOVICEPYROMANCER_H
#define NOVICEPYROMANCER_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "ActivatedAbilities.h"

class NovicePyromancer;
typedef std::shared_ptr<NovicePyromancer> NovicePyromancerPtr;

class NovicePyromancer : public ActivatedAbilities {
 public:
  NovicePyromancer(bool owner);
  ~NovicePyromancer();
};

#endif
