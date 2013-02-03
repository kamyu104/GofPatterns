#ifndef CoffeeMachineObserver_h
#define CoffeeMachineObserver_h

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
