#ifndef classic_Tea_h
#define classic_Tea_h

#include <utils/NoCopy.h>

namespace classic
{
    class Tea : public CaffeineBeverage
    {
    public:
      Tea()
	: CaffeineBeverage(m_recipe, "Tea", 1.27f)
	, m_recipe(200)
      {}

    private:
      TeaRecipe m_recipe;
      NO_COPY(Tea);
    };
}

#endif
