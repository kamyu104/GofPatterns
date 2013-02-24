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
  class BeverageFactory
  {
  private:
    typedef std::function<CaffeineBeverage*()> CreateFun;

  public:
  BeverageFactory()
    : m_factory()
      {/*
	m_factory["Coffee"] =
	  std::bind(
	       boost::factory<CaffeineBeverage*>(),
	       std::function<int ()>(std::bind(&Receipes::amountWaterMl, 150)),
	       &Receipes::brewCoffee);

	m_factory["Tea"] =
	  std::bind(
	       boost::factory<CaffeineBeverage*>(),
	       std::function<int ()>(std::bind(&Receipes::amountWaterMl, 200)),
               &Receipes::brewTea);
       */
	m_factory["Coffee"] = []
	  {
	    return new CaffeineBeverage(
	       []{ return 125; },
	       &Receipes::brewCoffee,
	       "Coffee",
	       2.48f);
	  };

	m_factory["Tea"] = []
	  {
	    return new CaffeineBeverage(
	       [] { return 200; },
               &Receipes::brewTea,
	       "Tea",
	       1.27f);
	  };
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
