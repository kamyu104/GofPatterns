#ifndef classic_Tea_h
#define classic_Tea_h

#include <utils/NoCopy.h>

namespace classic
{
    class Tea : public CaffeineBeverage
    {
    public:
      Tea()
	: CaffeineBeverage(m_receipe, "Tea", 1.27f)
	, m_receipe(200)
      {}

    private:
      TeaReceipe m_receipe;
      NO_COPY(Tea);
    };
}

#endif
