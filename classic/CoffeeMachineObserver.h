#ifndef classic_CoffeeMachineObserver_h
#define classic_CoffeeMachineObserver_h

#include <utils/NoCopy.h>

namespace classic
{
    class CoffeeMachineObserver
    {
    public:
      virtual void finished() = 0;
    };
}

#endif
