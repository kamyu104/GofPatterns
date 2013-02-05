#ifndef classic_CaffeineBeverage_h
#define classic_CaffeineBeverage_h

#include <classic/Receipe.h>
#include <classic/Condiment.h>
#include <utils/NoCopy.h>
#include <iostream>

namespace classic
{
    class CaffeineBeverage
    {
    public:
      CaffeineBeverage(Receipe& receipe)
      : m_receipe(receipe)
	, m_condiments(0)
      {}

      virtual ~CaffeineBeverage()
      {
	m_condiments = 0;
      }

      void prepareReceipe()
      {
	boilWater();
	m_receipe.brew();
	pourInCup();
	m_receipe.addCondiments();
	if(m_condiments) std::cout << m_condiments->description() << '\n';
      }

      void condiments(Condiment* condiments)
      {
	m_condiments = condiments;
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
      Condiment* m_condiments;

      NO_COPY(CaffeineBeverage);
    };
}

#endif
