#ifndef cpp11_Recipes_h
#define cpp11_Recipes_h

#include <iostream>

namespace cpp11
{
  class Recipes
  {
  public:
    static void brewCoffee()
    {
      std::cout << "dripping Coffee through filter\n";
    }

    static void brewTea()
    {
      std::cout << "steeping Tea\n";
    }

    static int amountWaterMl(int ml)
    {
      return ml;
    }

    NO_COPY_NO_MOVE(Recipes);
  };
}

#endif
