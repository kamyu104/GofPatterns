#ifndef classic_CoffeeRecipe_h
#define classic_CoffeeRecipe_h

#include <Recipe.h>
#include <utils/NoCopy.h>
#include <iostream>

namespace classic
{
    class CoffeeRecipe : public Recipe
    {
    public:
      CoffeeRecipe(int amountWaterMl)
        : Recipe()
	, m_amountWaterMl(amountWaterMl)
      {}

      virtual void brew()
      {
	std::cout << "dripping Coffee through filter\n";
      }

      virtual int amountWaterMl()
      {
	return m_amountWaterMl;
      }

    private:
      int m_amountWaterMl;

      NO_COPY(CoffeeRecipe);
    };
}

#endif
