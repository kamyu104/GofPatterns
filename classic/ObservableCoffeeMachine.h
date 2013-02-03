namespace classic
{
    class ObservableCoffeeMachine
    {
    private:
      typedef vector<CoffeeMachineObserver*> Observers;

    public:
      ObservableCoffeeMachine()
	: m_observers()
      {}

      void addObserver(Observers::value_type o)
      {
	m_observers.push_back(o);
      }

      void removeObserver(Observers::value_type o)
      {
	Observers::iterator it = find(m_observers.begin(), m_observers.end(), o);
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
