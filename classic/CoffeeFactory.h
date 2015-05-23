#ifndef classic_CoffeeFactory_h
#define classic_CoffeeFactory_h

#include <Coffee.h>
#include <utils/NoCopy.h>

namespace classic
{
    class CoffeeFactory : public CaffeineBeverageFactory
    {
    public:
      CoffeeFactory()
	: CaffeineBeverageFactory()
      {}

      virtual CaffeineBeverage* create()
      {
	return new Coffee();
      }

    private:
      NO_COPY(CoffeeFactory);
    };
}

#endif
