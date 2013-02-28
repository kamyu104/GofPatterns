#ifndef classic_Recipe_h
#define classic_Recipe_h

#include <utils/NoCopy.h>

namespace classic
{
    class Recipe
    {
    public:
      virtual int amountWaterMl() = 0;
      virtual void brew() = 0;
    };
}

#endif
