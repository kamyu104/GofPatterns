#ifndef CoffeeMachine_h
#define CoffeeMachine_h

#include <classic/ObservableCoffeeMachine.h>
#include <utils/NoCopy.h>
#include <string>

namespace classic
{
  class CoffeeMachineState;
  class Command;

  class CoffeeMachine : public ObservableCoffeeMachine
  {
  private:
    typedef std::vector<Command*> CommandQ;

  public:
  CoffeeMachine()
    : ObservableCoffeeMachine()
      , m_commands()
      , m_state(0)
      {}

    void setState(CoffeeMachineState* newState)
    {
      m_state = newState;
    }

    void execute(std::string const& cmd)
    {
      //m_state->action(*this, cmd);
    }

    void request(Command* c)
    {
      m_commands.push_back(c);
    }

    void start()
    {
      for(CommandQ::iterator it(m_commands.begin()); it != m_commands.end(); ++it)
	{
	  (*it)->execute();
	}
      this->notifyFinished();
    }

  private:
    CommandQ m_commands;
    CoffeeMachineState* m_state;

    NO_COPY(CoffeeMachine);
  };
}

#endif
