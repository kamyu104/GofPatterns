namespace classic
{
    class MilkFoam
    {
    public:
      MilkFoam()
      {}

      void makeFoam(int mlMilk)
      {
	boilMilk(mlMilk);
	pourInCup();
	foaming();
      }

    private:
      void boilMilk(int mlMilk)
      {
	cout << "boiling " << mlMilk << "ml milk\n";
      }

      void pourInCup()
      {
	cout << "pour in cup\n";
      }

      void foaming()
      {
	cout << "foaming\n";
      }

      NO_COPY(MilkFoam);
    };
}
