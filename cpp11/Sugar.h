#ifndef cpp11_Sugar_h
#define cpp11_Sugar_h

#include <string>

namespace cpp11
{
  class Sugar
  {
  public:
    static std::string description()
    {
      return "-Sugar-";
    }

    static float price()
    {
      return 0.07f;
    }
  };
}

#endif
