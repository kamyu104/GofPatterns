#ifndef cpp11_View_h
#define cpp11_View_h

#include <utils/NoCopyNoMove.h>
#include <iostream>

namespace cpp11
{
  class View
  {
  public:
    View()
      {}

    void coffeeMachineFinished()
    {
      std::cout << "Orders are ready to be served\n";
    }

  private:
    NO_COPY_NO_MOVE(View);
  };
}

#endif

