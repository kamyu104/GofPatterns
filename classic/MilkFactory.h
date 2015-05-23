#ifndef classic_MilkFactory_h
#define classic_MilkFactory_h

#include <CaffeineCondimentFactory.h>
#include <Milk.h>
#include <utils/NoCopy.h>

namespace classic
{
  class MilkFactory : public CaffeineCondimentFactory
    {
    public:
      MilkFactory()
	: CaffeineCondimentFactory()
	{}

      virtual ~MilkFactory()
      {}

      virtual Condiment* create(Condiment* condiment)
      {
	return new Milk(condiment);
      }

    private:
      NO_COPY(MilkFactory);
    };
}

#endif
