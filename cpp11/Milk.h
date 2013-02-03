#ifndef cpp11_Milk_h
#define cpp11_Milk_h

#include <string>

namespace cpp11
{
  class Milk
  {
  public:
    static std::string description()
    {
      return "-Milk-";
    }

    static float price()
    {
      return 0.13f;
    }
  };
}

#endif
