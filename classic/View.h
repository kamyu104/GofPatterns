#ifndef classic_View_h
#define classic_View_h

#include <utils/NoCopy.h>
#include <iostream>

namespace classic
{
    class View : public CoffeeMachineObserver
    {
    public:
      View()
	: CoffeeMachineObserver()
      {}

      virtual void finished()
      {
	std::cout << "Orders are ready to be served\n";
      }
    private:
      NO_COPY(View);
    };
}

#endif
