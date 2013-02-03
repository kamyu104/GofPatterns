#ifndef CaffeineBeverageFactory_h
#define CaffeineBeverageFactory_h

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
