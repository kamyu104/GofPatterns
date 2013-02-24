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
	, m_description("CaffeineBeverage")
	, m_price(0.0f)
      {}

      CaffeineBeverage(Receipe& receipe, std::string description, float price)
        : m_receipe(receipe)
	, m_condiments(0)
	, m_description(description)
	, m_price(price)
      {}

      virtual ~CaffeineBeverage()
      {
	if(m_condiments) delete m_condiments;
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

      void description()
      {
	std::cout << m_description;
	if(m_condiments)
	  {
	    std::cout << " : " << m_condiments->description();
	  }
	std::cout << '\n';
      }

      void price()
      {
	if(m_condiments)
	  {
	    std::cout << m_price + m_condiments->price() << '\n';
	  }
	else
	  {
	    std::cout << m_price << '\n';
	  }
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
      std::string m_description;
      float m_price;

      NO_COPY(CaffeineBeverage);
    };
}

#endif
