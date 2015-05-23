#ifndef cpp11_CondimentFactory_h
#define cpp11_CondimentFactory_h

#include <Condiment.h>
#include <Sugar.h>
#include <Milk.h>
#include <utils/NoCopyNoMove.h>
#include <string>
#include <map>

namespace cpp11
{
  class CondimentFactory
  {
  public:
  CondimentFactory()
    : m_factory()
      {
	Condiment sugar;
	sugar.description = &Sugar::description;
	sugar.price = &Sugar::price;
	m_factory["Sugar"] = sugar;

	Condiment milk;
	milk.description = &Milk::description;
	milk.price = &Milk::price;
	m_factory["Milk"] = milk;
      }

    Condiment create(std::string const& beverage)
    {
      return m_factory[beverage];
    }

  private:
    std::map<std::string, Condiment> m_factory;

    NO_COPY_NO_MOVE(CondimentFactory);
  };
}

#endif
