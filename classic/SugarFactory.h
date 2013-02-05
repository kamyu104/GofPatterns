#ifndef classic_SugarFactory_h
#define classic_SugarFactory_h

#include <classic/CaffeineCondimentFactory.h>
#include <classic/Sugar.h>
#include <utils/NoCopy.h>

namespace classic
{
  class SugarFactory : public CaffeineCondimentFactory
    {
    public:
      SugarFactory()
	: CaffeineCondimentFactory()
	{}

      virtual ~SugarFactory()
      {}

      virtual Condiment* create(Condiment* condiment)
      {
	return new Sugar(condiment);
      }

    private:
      NO_COPY(SugarFactory);
    };
}

#endif
