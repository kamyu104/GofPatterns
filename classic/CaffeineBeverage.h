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
	boilWater(m_receipe.amountWaterMl());
	m_receipe.brew();
	pourInCup();
	if(m_condiments) std::cout << m_condiments->description() << '\n';
      }

      void condiments(Condiment* condiments)
      {
	m_condiments = condiments;
      }

    private:
      void boilWater(int amountWaterMl)
      {
	std::cout << "boiling " << amountWaterMl << "ml water\n";
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
