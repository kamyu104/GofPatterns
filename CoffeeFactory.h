namespace classic
{
    class CoffeeFactory : public CaffeineBeverageFactory
    {
    public:
      CoffeeFactory()
	: CaffeineBeverageFactory()
      {}

      virtual CaffeineBeverage* create()
      {
	return new Coffee();
      }

    private:
      NO_COPY(CoffeeFactory);
    };
}
