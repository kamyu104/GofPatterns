#ifndef cpp11_Recipe_h
#define cpp11_Recipe_h

#include <functional>

namespace cpp11
{
  struct Recipe
  {
  public:
    std::function<void()> brew;
    std::function<void()> addCondiments;
  };
}

#endif
