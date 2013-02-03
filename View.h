namespace classic
{
    class View : public CoffeeMachineObserver
    {
    public:
      View()
	: CoffeeMachineObserver()
      {}

      virtual void finished()
      {
	cout << "Orders are ready to be served\n";
      }
    private:
      NO_COPY(View);
    };
}
