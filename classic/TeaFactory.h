#ifndef classic_TeaFactory_h
#define classic_TeaFactory_h

#include <classic/Tea.h>
#include <utils/NoCopy.h>

namespace classic
{
    class TeaFactory : public CaffeineBeverageFactory
    {
    public:
      TeaFactory()
	: CaffeineBeverageFactory()
      {}

      virtual CaffeineBeverage* create()
      {
	return new Tea();
      }

    private:
      NO_COPY(TeaFactory);
    };
}

#endif
