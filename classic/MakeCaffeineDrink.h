#ifndef MakeCaffeineDrink_h
#define MakeCaffeineDrink_h

#include <utils/NoCopy.h>
#include <classic/Command.h>

namespace classic
{
    class MakeCaffeineDrink : public Command
    {
    public:
      MakeCaffeineDrink(CaffeineBeverage& drink)
      : Command()
      , m_drink(drink)
      {}

      virtual void execute()
      {
	m_drink.prepareReceipe();
      }

    private:
      CaffeineBeverage& m_drink;

      NO_COPY(MakeCaffeineDrink);
    };
}

#endif
