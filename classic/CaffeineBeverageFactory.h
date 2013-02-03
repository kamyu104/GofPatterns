#ifndef classic_CaffeineBeverageFactory_h
#define classic_CaffeineBeverageFactory_h

#include <utils/NoCopy.h>

namespace classic
{
    class CaffeineBeverageFactory
    {
    public:
      virtual ~CaffeineBeverageFactory()
      {}

      virtual CaffeineBeverage* create() = 0;
    };
}

#endif
