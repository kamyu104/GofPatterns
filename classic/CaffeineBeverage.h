#ifndef classic_CaffeineBeverage_h
#define classic_CaffeineBeverage_h

#include <classic/Recipe.h>
#include <classic/Condiment.h>
#include <utils/NoCopy.h>
#include <iostream>

namespace classic
{
    class CaffeineBeverage
    {
    public:
      CaffeineBeverage(Recipe& recipe)
        : m_recipe(recipe)
	, m_condiments(0)
	, m_description("CaffeineBeverage")
	, m_price(0.0f)
      {}

      CaffeineBeverage(Recipe& recipe, std::string description, float price)
        : m_recipe(recipe)
	, m_condiments(0)
	, m_description(description)
	, m_price(price)
      {}

      virtual ~CaffeineBeverage()
      {
	if(m_condiments) delete m_condiments;
      }

      void prepare()
      {
	boilWater(m_recipe.amountWaterMl());
	m_recipe.brew();
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

      Recipe& m_recipe;
      Condiment* m_condiments;
      std::string m_description;
      float m_price;

      NO_COPY(CaffeineBeverage);
    };
}

#endif
