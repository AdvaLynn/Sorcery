#ifndef GUARD_
#define GUARD_
#include <vector>
#include "TriggeredAbilities.h"
#include <memory>
#include <string>

class Guardian;
typedef std::shared_ptr<Guardian> GuardianPtr;

class Guardian : public TriggeredAbilities {
 public:
  Guardian(bool owner);
  ~Guardian();
};

#endif
