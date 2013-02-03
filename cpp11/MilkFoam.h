#ifndef cpp11_MilkFoam_h
#define cpp11_MilkFoam_h

#include <utils/NoCopyNoMove.h>
#include <iostream>

namespace cpp11
{
  class MilkFoam
  {
  public:
    MilkFoam()
      {}

    void makeFoam(int mlMilk)
    {
      boilMilk(mlMilk);
      pourInCup();
      foaming();
    }

  private:
    void boilMilk(int mlMilk)
    {
      std::cout << "boiling " << mlMilk << "ml milk\n";
    }

    void pourInCup()
    {
      std::cout << "pour in cup\n";
    }

    void foaming()
    {
      std::cout << "foaming\n";
    }

    NO_COPY_NO_MOVE(MilkFoam);
  };
}

#endif
