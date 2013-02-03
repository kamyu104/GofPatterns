namespace classic
{
    class Sugar : public Condiment
    {
    public:
      Sugar()
	: Condiment()
      {}

      Sugar(Condiment* next)
      : Condiment(next)
      {}

    private:
      virtual string onDescription()
      {
	return "-Sugar-";
      }

      virtual float onPrice()
      {
	return 0.07f;
      }

      NO_COPY(Sugar);
    };
}
