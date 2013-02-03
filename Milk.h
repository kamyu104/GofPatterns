namespace classic
{
    class Milk : public Condiment
    {
    public:
      Milk()
	: Condiment()
      {}

      Milk(Condiment* next)
      : Condiment(next)
      {}

    private:
      virtual string onDescription()
      {
	return "-Milk-";
      }

      virtual float onPrice()
      {
	return 0.13f;
      }

      NO_COPY(Milk);
    };
}
