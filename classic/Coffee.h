#ifndef classic_Coffee_h
#define classic_Coffee_h

#include <utils/NoCopy.h>

namespace classic
{
    class Coffee : public CaffeineBeverage
    {
    public:
      Coffee()
	: CaffeineBeverage(m_recipe, "Coffee", 2.98f)
	, m_recipe(125)
      {}

    private:
      CoffeeRecipe m_recipe;
      NO_COPY(Coffee);
    };
}

#endif
