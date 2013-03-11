#ifndef cpp11_BeverageFactory_h
#define cpp11_BeverageFactory_h

#include <cpp11/Recipes.h>
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
      {
	m_factory["Coffee"] =
	  std::bind(
		    boost::factory<CaffeineBeverage*>(),
	       std::function<int ()>(std::bind(&Recipes::amountWaterMl, 150)),
	       &Recipes::brewCoffee);

	m_factory["Tea"] =
	  std::bind(
		    boost::factory<CaffeineBeverage*>(),
	       std::function<int ()>(std::bind(&Recipes::amountWaterMl, 200)),
               &Recipes::brewTea);
       
	/* m_factory["Coffee"] = [] */
	/*   { */
	/*     return new CaffeineBeverage( */
	/*        []{ return 125; }, */
	/*        &Recipes::brewCoffee, */
	/*        "Coffee", */
	/*        2.48f); */
	/*   }; */

	/* m_factory["Tea"] = [] */
	/*   { */
	/*     return new CaffeineBeverage( */
	/*        [] { return 200; }, */
        /*        &Recipes::brewTea, */
	/*        "Tea", */
	/*        1.27f); */
	/*   }; */
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
