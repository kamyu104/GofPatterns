namespace classic
{
    class CaffeineBeverage
    {
    public:
      CaffeineBeverage(Receipe& receipe)
      : m_receipe(receipe)
      {}

      virtual ~CaffeineBeverage()
      {}

      void prepareReceipe()
      {
	boilWater();
	m_receipe.brew();
	pourInCup();
	m_receipe.addCondiments();
      }

    private:
      void boilWater()
      {
	cout << "boil water\n";
      }

      void pourInCup()
      {
	cout << "pour in cup\n";
      }

      Receipe& m_receipe;

      NO_COPY(CaffeineBeverage);
    };
}
