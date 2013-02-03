#ifndef classic_CoffeeMachineState_h
#define classic_CoffeeMachineState_h

#include <utils/NoCopy.h>
#include <string>

namespace classic
{
  class CoffeeMachine;

  class CoffeeMachineState
  {
  public:
    virtual void action(CoffeeMachine& coffeeMachine, string const& cmd) = 0;
  };
}

#endif
