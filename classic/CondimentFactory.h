#ifndef classic_CondimentFactory_h
#define classic_CondimentFactory_h

#include <classic/CaffeineCondimentFactory.h>
#include <classic/Condiment.h>
#include <classic/MilkFactory.h>
#include <classic/SugarFactory.h>
#include <utils/NoCopy.h>
#include <string>
#include <map>

namespace classic
{
    class CondimentFactory
    {
    public:
      CondimentFactory()
	: m_factory()
      {
	m_factory["Milk"] = new MilkFactory();
	m_factory ["Sugar"] = new SugarFactory();
      }

      ~CondimentFactory()
      {
	delete m_factory["Milk"];
	delete m_factory["Sugar"];
      }

      Condiment* create(std::string const& condiment, Condiment* nextCondiment)
      {
	return m_factory[condiment]->create(nextCondiment);
      }

    private:
      std::map<std::string, CaffeineCondimentFactory*> m_factory;

      NO_COPY(CondimentFactory);
    };
}

#endif
