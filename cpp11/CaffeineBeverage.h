#ifndef cpp11_CaffeineBeverage_h
#define cpp11_CaffeineBeverage_h

#include <cpp11/Receipe.h>
#include <utils/NoCopyNoMove.h>
#include <functional>
#include <iostream>

namespace cpp11
{
  class CaffeineBeverage
  {
  public:
  CaffeineBeverage(Receipe receipe)
    : m_brew(receipe.brew)
      , m_addCondiments(receipe.addCondiments)
      {}

  CaffeineBeverage(std::function<void()> brew, std::function<void()> addCondiments)
    : m_brew(brew)
      , m_addCondiments(addCondiments)
    {}

    void prepareReceipe()
    {
      boilWater();
      m_brew();
      pourInCup();
      m_addCondiments();
    }

  private:
    void boilWater()
    {
      std::cout << "boil water\n";
    }

    void pourInCup()
    {
      std::cout << "pour in cup\n";
    }

    std::function<void()> m_brew;
    std::function<void()> m_addCondiments;

    NO_COPY_NO_MOVE(CaffeineBeverage);
  };
}

#endif
