#ifndef MilkFoam_h
#define MilkFoam_h

#include <utils/NoCopy.h>
#include <iostream>

namespace classic
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

      NO_COPY(MilkFoam);
    };
}

#endif
