#ifndef classic_CoffeeReceipe_h
#define classic_CoffeeReceipe_h

#include <classic/Receipe.h>
#include <utils/NoCopy.h>
#include <iostream>

namespace classic
{
    class CoffeeReceipe : public Receipe
    {
    public:
      CoffeeReceipe(int amountWaterMl)
        : Receipe()
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

      NO_COPY(CoffeeReceipe);
    };
}

#endif
