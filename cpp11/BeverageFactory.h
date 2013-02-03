#ifndef cpp11_BeverageFactory_h
#define cpp11_BeverageFactory_h

#include <cpp11/Receipes.h>
#include <cpp11/CaffeineBeverage.h>
#include <utils/NoCopyNoMove.h>
#include <boost/functional/factory.hpp>
#include <functional>
#include <memory>
#include <string>
#include <map>

namespace cpp11
{
  class CaffeineBeverage;

  class BeverageFactory
  {
  private:
    typedef std::function<CaffeineBeverage*()> CreateFun;

  public:
  BeverageFactory()
    : m_factory()
      {
	/* todo
	m_factory["Coffee"] =
	  std::bind(
	       boost::factory<CaffeineBeverage*>(),
	       std::bind(&Receipes::brewCoffee, 1),
	       &Receipes::addSugarAndMilk);

	m_factory["Tea"] =
	  std::bind(
	       boost::factory<CaffeineBeverage*>(),
	       std::bind(&Receipes::brewTea, 1),
	       &Receipes::addLemon);*/
      }

    std::unique_ptr<CaffeineBeverage> create(std::string const& beverage)
      {
	return std::unique_ptr<CaffeineBeverage>(m_factory[beverage]());
      }

  private:
    std::map<std::string, CreateFun> m_factory;

    NO_COPY_NO_MOVE(BeverageFactory);
  };
}

#endif
