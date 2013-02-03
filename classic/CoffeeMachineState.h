namespace classic
{
    class CoffeeMachineState
    {
    public:
      virtual void action(CoffeeMachine& coffeeMachine, string const& cmd) = 0;
    };
}
