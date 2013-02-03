namespace classic
{
    class CoffeeMachine : public ObservableCoffeeMachine
    {
    private:
      typedef vector<Command*> CommandQ;

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

      void execute(string const& cmd)
      {
	m_state->action(*this, cmd);
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
