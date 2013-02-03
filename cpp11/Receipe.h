#ifndef cpp11_Receipe_h
#define cpp11_Receipe_h

#include <functional>

namespace cpp11
{
  struct Receipe
  {
  public:
    std::function<void()> brew;
    std::function<void()> addCondiments;
  };
}

#endif
