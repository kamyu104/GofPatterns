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

    static int amountWaterCoffeeMl()
    {
      return 150;
    }

    static int amountWaterTeaMl()
    {
      return 200;
    }

    NO_COPY_NO_MOVE(Recipes);
  };
}

#endif
