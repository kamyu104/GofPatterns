#ifndef classic_Receipe_h
#define classic_Receipe_h

#include <utils/NoCopy.h>

namespace classic
{
    class Receipe
    {
    public:
      virtual void brew() = 0;
      virtual void addCondiments() = 0;
    };
}

#endif
