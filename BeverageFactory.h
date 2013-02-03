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

      CaffeineBeverage* create(string const& beverage)
      {
	return m_factory[beverage]->create();
      }

    private:
      map<string, CaffeineBeverageFactory*> m_factory;

      NO_COPY(BeverageFactory);
    };
}
