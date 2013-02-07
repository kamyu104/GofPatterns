#ifndef cpp11_Condiment_h
#define cpp11_Condiment_h

#include <functional>
#include <string>

namespace cpp11
{
  struct Condiment
  {
  public:
    std::function<std::string()> description;
    std::function<float()> price;
  };
}

#endif
