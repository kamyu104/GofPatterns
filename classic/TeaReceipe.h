#ifndef classic_TeaReceipe_h
#define classic_TeaReceipe_h

#include <utils/NoCopy.h>
#include <iostream>

namespace classic
{
    class TeaReceipe : public Receipe
    {
    public:
      TeaReceipe(int amountWaterMl)
        : Receipe()
        , m_amountWaterMl(amountWaterMl)
      {}

      virtual void brew()
      {
	std::cout << "steeping Tea\n";
      }

      virtual int amountWaterMl()
      {
	return m_amountWaterMl;
      }

    private:
      int m_amountWaterMl;

      NO_COPY(TeaReceipe);
    };
}

#endif
