#ifndef classic_ObservableCoffeeMachine_h
#define classic_ObservableCoffeeMachine_h

#include <CoffeeMachineObserver.h>
#include <utils/NoCopy.h>
#include <vector>
#include <algorithm>

namespace classic
{
    class ObservableCoffeeMachine
    {
    private:
      typedef std::vector<CoffeeMachineObserver*> Observers;

    public:
      ObservableCoffeeMachine()
	: m_observers()
      {}

      void addObserver(Observers::value_type o)
      {
	Observers::iterator it = std::find(m_observers.begin(), m_observers.end(), o);
	if(it == m_observers.end()) m_observers.push_back(o);
      }

      void removeObserver(Observers::value_type o)
      {
	Observers::iterator it = std::find(m_observers.begin(), m_observers.end(), o);
	if(it != m_observers.end()) m_observers.erase(it);
      }

    protected:
      void notifyFinished()
      {
	for(Observers::iterator it(m_observers.begin()); it != m_observers.end(); ++it)
	  {
	    (*it)->finished();
	  }
      }

    private:
      Observers m_observers;

      NO_COPY(ObservableCoffeeMachine);
    };
}

#endif
