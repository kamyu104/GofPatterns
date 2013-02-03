#ifndef BeverageFactory_h
#define BeverageFactory_h

#include <classic/CaffeineBeverageFactory.h>
#include <classic/CoffeeFactory.h>
#include <classic/TeaFactory.h>
#include <utils/NoCopy.h>
#include <string>
#include <map>

namespace classic
{
    class BeverageFactory
    {
    public:
      BeverageFactory()
	: m_factory()
      {
	m_factory["Coffee"] = new CoffeeFactory();
	m_factory ["Tea"] = new TeaFactory();
      }

      ~BeverageFactory()
      {
	delete m_factory["Coffee"];
	delete m_factory["Tea"];
      }

      CaffeineBeverage* create(std::string const& beverage)
      {
	return m_factory[beverage]->create();
      }

    private:
      std::map<std::string, CaffeineBeverageFactory*> m_factory;

      NO_COPY(BeverageFactory);
    };
}

#endif
