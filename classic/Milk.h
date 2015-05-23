#ifndef classic_Milk_h
#define classic_Milk_h

#include <Condiment.h>
#include <utils/NoCopy.h>
#include <string>


namespace classic
{
    class Milk : public Condiment
    {
    public:
      Milk()
	: Condiment()
      {}

      Milk(Condiment* next)
      : Condiment(next)
      {}

    private:
      virtual std::string onDescription()
      {
	return "-Milk-";
      }

      virtual float onPrice()
      {
	return 0.13f;
      }

      NO_COPY(Milk);
    };
}

#endif
