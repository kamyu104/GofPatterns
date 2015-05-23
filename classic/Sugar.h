#ifndef classic_Sugar_h
#define classic_Sugar_h

#include <Condiment.h>
#include <utils/NoCopy.h>
#include <string>

namespace classic
{
    class Sugar : public Condiment
    {
    public:
      Sugar()
	: Condiment()
      {}

      Sugar(Condiment* next)
      : Condiment(next)
      {}

    private:
      virtual std::string onDescription()
      {
	return "-Sugar-";
      }

      virtual float onPrice()
      {
	return 0.07f;
      }

      NO_COPY(Sugar);
    };
}

#endif
