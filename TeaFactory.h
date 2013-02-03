namespace classic
{
    class TeaFactory : public CaffeineBeverageFactory
    {
    public:
      TeaFactory()
	: CaffeineBeverageFactory()
      {}

      virtual CaffeineBeverage* create()
      {
	return new Tea();
      }

    private:
      NO_COPY(TeaFactory);
    };
}
