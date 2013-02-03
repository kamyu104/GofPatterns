namespace classic
{
    class CoffeeReceipe : public Receipe
    {
    public:
      CoffeeReceipe(int minutes)
      : Receipe()
      , m_minutes(minutes)
      {}

      virtual void brew()
      {
	cout << m_minutes << "min dripping Coffee through filter\n";
      }

      virtual void addCondiments()
      {
	cout << "Adding Sugar and Milk\n";
      }

    private:
      int m_minutes;

      NO_COPY(CoffeeReceipe);
    };
}
