#ifndef classic_Coffee_h
#define classic_Coffee_h

#include <utils/NoCopy.h>

namespace classic
{
    class Coffee : public CaffeineBeverage
    {
    public:
      Coffee()
	: CaffeineBeverage(m_receipe, "Coffee", 2.98f)
	, m_receipe(125)
      {}

    private:
      CoffeeReceipe m_receipe;
      NO_COPY(Coffee);
    };
}

#endif
