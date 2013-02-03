#ifndef classic_CaffeineBeverage_h
#define classic_CaffeineBeverage_h

#include <utils/NoCopy.h>
#include <iostream>

namespace classic
{
    class CaffeineBeverage
    {
    public:
      CaffeineBeverage(Receipe& receipe)
      : m_receipe(receipe)
      {}

      virtual ~CaffeineBeverage()
      {}

      void prepareReceipe()
      {
	boilWater();
	m_receipe.brew();
	pourInCup();
	m_receipe.addCondiments();
      }

    private:
      void boilWater()
      {
	std::cout << "boil water\n";
      }

      void pourInCup()
      {
	std::cout << "pour in cup\n";
      }

      Receipe& m_receipe;

      NO_COPY(CaffeineBeverage);
    };
}

#endif
