#ifndef cpp11_accu_h
#define cpp11_accu_h

#include <functional>

namespace cpp11
{
  template<typename Res>
    static Res accu(std::function<Res()> call, std::function<Res()> next)
    {
      if(next) return call() + next();
      return call();
    }
}

#endif
