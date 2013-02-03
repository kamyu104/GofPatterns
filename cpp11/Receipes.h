#ifndef cpp11_Receipes_h
#define cpp11_Receipes_h

#include <iostream>

namespace cpp11
{
  class Receipes
  {
  public:
    static void brewCoffee(int minutes)
    {
      std::cout << minutes << "min for dripping Coffee through filter\n";
    }

    static void brewTea(int minutes)
    {
      std::cout << minutes << "min for steeping Tea\n";
    }

    static void addSugarAndMilk()
    {
      std::cout << "Adding Sugar and Milk\n";
    }

    static void addLemon()
    {
      std::cout << "Adding Lemon\n";
    }

    NO_COPY_NO_MOVE(Receipes);
  };
}

#endif
