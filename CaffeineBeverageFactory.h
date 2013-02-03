namespace classic
{
    class CaffeineBeverageFactory
    {
    public:
      virtual ~CaffeineBeverageFactory()
      {}

      virtual CaffeineBeverage* create() = 0;
    };
}
