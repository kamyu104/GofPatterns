#ifndef classic_CaffeineCondimentFactory_h
#define classic_CaffeineCondimentFactory_h

#include <Condiment.h>
#include <utils/NoCopy.h>

namespace classic
{
    class CaffeineCondimentFactory
    {
    public:
      virtual ~CaffeineCondimentFactory()
      {}

      virtual Condiment* create(Condiment*) = 0;
    };
}

#endif
