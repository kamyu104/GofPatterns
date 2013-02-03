#ifndef CoffeeReceipe_h
#define CoffeeReceipe_h

#include <classic/Receipe.h>
#include <utils/NoCopy.h>
#include <iostream>

namespace classic
{
    class CoffeeReceipe : public Receipe
    {
    public:
      CoffeeReceipe(int minutes)
      : Receipe()
      , m_minutes(minutes)
      {}

      virtual void brew()
      {
	std::cout << m_minutes << "min dripping Coffee through filter\n";
      }

      virtual void addCondiments()
      {
	std::cout << "Adding Sugar and Milk\n";
      }

    private:
      int m_minutes;

      NO_COPY(CoffeeReceipe);
    };
}

#endif
