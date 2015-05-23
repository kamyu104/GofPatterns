#ifndef cpp11_CaffeineBeverage_h
#define cpp11_CaffeineBeverage_h

#include <Condiment.h>
#include <utils/NoCopyNoMove.h>
#include <functional>
#include <iostream>
#include <string>

namespace cpp11
{
  class CaffeineBeverage
  {
  public:
  CaffeineBeverage(std::function<int()> amountWaterMl, std::function<void()> brew)
    : m_brew(brew)
      , m_amountWaterMl(amountWaterMl)
      , m_description("CaffeineBeverage")
      , m_price(0.0f)
      , m_condiment()
      {}

  CaffeineBeverage(std::function<int()> amountWaterMl, std::function<void()> brew, std::string description, float price)
    : m_brew(brew)
      , m_amountWaterMl(amountWaterMl)
      , m_description(description)
      , m_price(price)
      , m_condiment()
      {}

    void prepare()
    {
      boilWater(m_amountWaterMl());
      m_brew();
      pourInCup();
      addCondiments();
    }

    void condiments(Condiment condiment)
    {
      m_condiment = condiment;
    }

    void description() const
      {
	std::string condiment = m_condiment.description ? " : " + m_condiment.description() : "";
	std::cout << m_description << condiment << '\n';
      }

    void price() const
    {
      float condimentsPrice = m_condiment.price ? m_condiment.price() : 0.0f;
      std::cout << m_price + condimentsPrice << '\n';
    }

  private:
    void boilWater(int amountWaterMl)
    {
      std::cout << "boiling " << amountWaterMl << "ml water\n";
    }

    void pourInCup() const
    {
      std::cout << "pour in cup\n";
    }

    void addCondiments() const
    {
      if(m_condiment.description) std::cout << m_condiment.description() << '\n';
    }

    std::function<void()> m_brew;
    std::function<int()> m_amountWaterMl;
    std::string m_description;
    float m_price;
    Condiment m_condiment;

    NO_COPY_NO_MOVE(CaffeineBeverage);
  };
}

#endif
