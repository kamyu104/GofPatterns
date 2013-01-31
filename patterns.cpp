// /Users/Tobias/Downloads/checker-270/bin/clang++ -std=c++0x -stdlib=libc++ -I/Developer/Library/boost_1_51_0 -o patterns_clang patterns.cpp

// /Users/Tobias/Downloads/checker-270/scan-build -V -o ./scan /Users/Tobias/Downloads/checker-270/bin/clang++ -std=c++0x -stdlib=libc++ -I/Developer/Library/boost_1_51_0 -o patterns_clang patterns.cpp

// g++ --std=C++0x -o patterns_gcc patterns.cpp

// D:\Projects\C++\gcc_4.7_20110903\bin\g++.exe --std=c++0x patterns.cpp -o patterns_gcc

// D:\Projects\C++\llvm\build\bin\Debug\clang++ -std=c++0x -stdlib=libc++ -o patterns_clang patterns.cpp

// "C:\Program Files\Microsoft Visual Studio 10.0\VC\bin\vcvars32.bat" & "C:\Program Files\Microsoft Visual Studio 10.0\VC\bin\cl.exe" /EHsc /nologo /W4 /NTd patterns.cpp

#include <boost/signals2.hpp>
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>

#define NO_COPY(className)			\
  private: className(className const&);		\
private: className& operator=(className const&)

#define NO_MOVE(className)			\
  private: className(className&&);		\
private: className&& operator=(className&&)

#define NO_COPY_NO_MOVE(className)		\
  NO_COPY(className);				\
  NO_MOVE(className)

using namespace std;

namespace classic
{

  namespace beverage
  {

    class Receipe
    {
    public:
      virtual void brew() = 0;
      virtual void addCondiments() = 0;
    };

    class CaffeineBeverage
    {
    public:
      CaffeineBeverage(Receipe& receipe)
      : m_receipe(receipe)
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

    class TeaReceipe : public Receipe
    {
    public:
      TeaReceipe(int minutes)
      : Receipe()
      , m_minutes(minutes)
      {}

      virtual void brew()
      {
	cout << m_minutes << "min steeping Tea through filter\n";
      }

      virtual void addCondiments()
      {
	cout << "Adding Lemon\n";
      }

    private:
      int m_minutes;

      NO_COPY(TeaReceipe);
    };

    class Condiment
    {
    public:
      Condiment()
	: m_next(0)
      {}

      Condiment(Condiment* next)
      : m_next(next)
      {}

      string description()
      {
	if(m_next) return this->onDescription() + m_next->description();
	return this->onDescription();
      }
      float price()
      {
	if(m_next) return this->onPrice() + m_next->price();
	return this->onPrice();
      }

    private:
      virtual string onDescription() = 0;
      virtual float onPrice() = 0;

      Condiment* m_next;
    };


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

    class Command
    {
    public:
      virtual void execute() = 0;
    };

    class CoffeeMachine;

    class CoffeeMachineState
    {
    public:
      virtual void action(CoffeeMachine& coffeeMachine, string const& cmd) = 0;
    };

    class CoffeeMachineObserver
    {
    public:
      virtual void finished() = 0;
    };

    class View : public CoffeeMachineObserver
    {
    public:
      View()
	: CoffeeMachineObserver()
      {}

      virtual void finished()
      {
	cout << "Orders are ready to be served\n";
      }
    private:
      NO_COPY(View);
    };

    class ObservableCoffeeMachine
    {
    private:
      typedef vector<CoffeeMachineObserver*> Observers;

    public:
      ObservableCoffeeMachine()
	: m_observers()
      {}

      void addObserver(Observers::value_type o)
      {
	m_observers.push_back(o);
      }

      void removeObserver(Observers::value_type o)
      {
	Observers::iterator it = find(m_observers.begin(), m_observers.end(), o);
	if(it != m_observers.end()) m_observers.erase(it);
      }

    protected:
      void notifyFinished()
      {
	for(Observers::iterator it(m_observers.begin()); it != m_observers.end(); ++it)
	  {
	    (*it)->finished();
	  }
      }

    private:
      Observers m_observers;

      NO_COPY(ObservableCoffeeMachine);
    };

    class CoffeeMachine : public ObservableCoffeeMachine
    {
    private:
      typedef vector<Command*> CommandQ;

    public:
      CoffeeMachine()
	: ObservableCoffeeMachine()
	, m_commands()
	, m_state(0)
      {}

      void setState(CoffeeMachineState* newState)
      {
	m_state = newState;
      }

      void execute(string const& cmd)
      {
	m_state->action(*this, cmd);
      }

      void request(Command* c)
      {
	m_commands.push_back(c);
      }

      void start()
      {
	for(CommandQ::iterator it(m_commands.begin()); it != m_commands.end(); ++it)
	  {
	    (*it)->execute();
	  }
	this->notifyFinished();
      }

    private:
      CommandQ m_commands;
      CoffeeMachineState* m_state;

      NO_COPY(CoffeeMachine);
    };

    class MakeCaffeineDrink : public Command
    {
    public:
      MakeCaffeineDrink(CaffeineBeverage& drink)
      : Command()
      , m_drink(drink)
      {}

      virtual void execute()
      {
	m_drink.prepareReceipe();
      }

    private:
      CaffeineBeverage& m_drink;

      NO_COPY(MakeCaffeineDrink);
    };

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

    class MakeMilkFoam : public Command
    {
    public:
      MakeMilkFoam(MilkFoam& milk, int mlMilk)
	: Command()
	, m_milk(milk)
	, m_mlMilk(mlMilk)
      {}

      virtual void execute()
      {
	m_milk.makeFoam(m_mlMilk);
      }

      void setMlMilk(int mlMilk)
      {
	m_mlMilk = mlMilk;
      }

    private:
      MilkFoam& m_milk;
      int m_mlMilk;

      NO_COPY(MakeMilkFoam);
    };
  }

}

namespace cpp11
{

  namespace beverages
  {

    struct Receipe
    {
    public:
      function<void()> brew;
      function<void()> addCondiments;
    };

    class CaffeineBeverage
    {
    public:
      CaffeineBeverage(Receipe receipe)
      : m_brew(receipe.brew)
      , m_addCondiments(receipe.addCondiments)
      {}

      CaffeineBeverage(function<void()> brew, function<void()> addCondiments)
	: m_brew(brew)
	, m_addCondiments(addCondiments)
      {}

      void prepareReceipe()
      {
	boilWater();
	m_brew();
	pourInCup();
	m_addCondiments();
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

      function<void()> m_brew;
      function<void()> m_addCondiments;

      NO_COPY_NO_MOVE(CaffeineBeverage);
    };

    class Receipes
    {
    public:
      static void brewCoffee(int minutes)
      {
	cout << minutes << "min for dripping Coffee through filter\n";
      }

      static void brewTea(int minutes)
      {
	cout << minutes << "min for steeping Tea\n";
      }

      static void addSugarAndMilk()
      {
	cout << "Adding Sugar and Milk\n";
      }

      static void addLemon()
      {
	cout << "Adding Lemon\n";
      }

      NO_COPY_NO_MOVE(Receipes);
    };

    class CoffeeMachine
    {
    private:
      typedef vector<function<void()>> CommandQ;

    public:
      CoffeeMachine()
	: m_commands()
	, m_sigFinished()
      {}

      void request(CommandQ::value_type c)
      {
	m_commands.push_back(c);
      }

      void start()
      {
	for_each(
		 begin(m_commands), end(m_commands),
		 [](CommandQ::value_type c){ c(); });
	m_sigFinished();
      }

      void getNotifiedOnFinished(function<void()> callback)
      {
	m_sigFinished.connect(callback);
      }

    private:
      CommandQ m_commands;
      boost::signals2::signal<void()> m_sigFinished;

      NO_COPY_NO_MOVE(CoffeeMachine);
    };

    class View
    {
    public:
      View()
      {}

      void coffeeMachineFinished()
      {
	cout << "Orders are ready to be served\n";
      }

    private:
      NO_COPY_NO_MOVE(View);
    };

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

      NO_COPY_NO_MOVE(MilkFoam);
    };

    template<typename Res>
    static Res accu(function<Res()> call, function<Res()> next)
    {
      if(next) return call() + next();
      return call();
    }

    class Milk
    {
    public:
      static string description()
      {
	return "-Milk-";
      }

      static float price()
      {
	return 0.13f;
      }
    };

    class Sugar
    {
    public:
      static string description()
      {
	return "-Sugar-";
      }

      static float price()
      {
	return 0.07f;
      }
    };
  }

}

int main(int argc, char* argv[])
{
  {
    using namespace classic;
    {
      using namespace beverage;

      CoffeeReceipe coffeeReceipe(1);
      TeaReceipe teaReceipe(2);

      CaffeineBeverage coffee(coffeeReceipe);
      CaffeineBeverage tea(teaReceipe);

      typedef vector<CaffeineBeverage*> Beverages;
      Beverages beverages;

      beverages.push_back(&coffee);
      beverages.push_back(&tea);

      for(Beverages::iterator it(beverages.begin()); it != beverages.end(); ++it)
	{
	  (*it)->prepareReceipe();
	}

      MakeCaffeineDrink makeCoffee(coffee);
      MilkFoam milkFoam;
      MakeMilkFoam makeMilkFoam(milkFoam, 100);
      
      CoffeeMachine coffeeMachine;
      View view;

      coffeeMachine.addObserver(&view);

      coffeeMachine.request(&makeCoffee);
      coffeeMachine.request(&makeMilkFoam);
      coffeeMachine.start();

      makeMilkFoam.setMlMilk(200);
      coffeeMachine.request(&makeMilkFoam);
      makeMilkFoam.setMlMilk(300);
      coffeeMachine.request(&makeMilkFoam);
      coffeeMachine.start();

      Milk milk;
      Sugar sugarMilk(&milk);
      Sugar doubleSugarMilk(&sugarMilk);

      cout << "Condiments: " << doubleSugarMilk.description() << '\n';
      cout << "Price: " << doubleSugarMilk.price() << '\n';
    }
  }

  {
    using namespace cpp11;
    {
      using namespace beverages;

      CaffeineBeverage coffee(bind(&Receipes::brewCoffee, 1), &Receipes::addSugarAndMilk);
      CaffeineBeverage tea(bind(&Receipes::brewTea, 2), &Receipes::addLemon);

      typedef vector<CaffeineBeverage*> Beverages;
      Beverages beverages;

      beverages.push_back(&coffee);
      beverages.push_back(&tea);

      for_each(
	       begin(beverages), end(beverages),
	       bind(&CaffeineBeverage::prepareReceipe, placeholders::_1));

      CoffeeMachine coffeeMachine;
      View view;
      coffeeMachine.getNotifiedOnFinished(bind(&View::coffeeMachineFinished, &view));

      coffeeMachine.request(bind(&CaffeineBeverage::prepareReceipe, &coffee));
      coffeeMachine.request(bind(&CaffeineBeverage::prepareReceipe, &tea));

      MilkFoam milkFoam;
      coffeeMachine.request(bind(&MilkFoam::makeFoam, &milkFoam, 100));

      coffeeMachine.start();

      coffeeMachine.request(bind(&MilkFoam::makeFoam, &milkFoam, 200));
      coffeeMachine.request(bind(&MilkFoam::makeFoam, &milkFoam, 300));
      coffeeMachine.start();

      function<string()> condimentDescription;
      condimentDescription = bind(&accu<string>, &Milk::description, condimentDescription);
      condimentDescription = bind(&accu<string>, &Sugar::description, condimentDescription);
      condimentDescription = bind(&accu<string>, &Sugar::description, condimentDescription);

      function<float()> condimentPrice;
      condimentPrice = bind(&accu<float>, &Milk::price, condimentPrice);
      condimentPrice = bind(&accu<float>, &Sugar::price, condimentPrice);
      condimentPrice = bind(&accu<float>, &Sugar::price, condimentPrice);

      cout << "Condiments: " << condimentDescription() << '\n';
      cout << "Price: " << condimentPrice() << '\n';
    }

#if defined(__GNUC__) || defined(__clang__)
    using namespace cpp11;
    {
      using namespace beverages;

      CaffeineBeverage coffee([]{ Receipes::brewCoffee(1); }, []{ Receipes::addSugarAndMilk(); });
      CaffeineBeverage tea([]{ Receipes::brewTea(2); }, []{ Receipes::addLemon(); });

      typedef vector<CaffeineBeverage*> Beverages;
      Beverages beverages;

      beverages.push_back(&coffee);
      beverages.push_back(&tea);

      using namespace placeholders;

      for(auto beverage : beverages){ beverage->prepareReceipe(); }

      CoffeeMachine coffeeMachine;
      View view;
      coffeeMachine.getNotifiedOnFinished([&]{ view.coffeeMachineFinished(); });

      MilkFoam milkFoam;
      coffeeMachine.request([&]{ milkFoam.makeFoam(100); });
      coffeeMachine.request([&]{ coffee.prepareReceipe(); });
      coffeeMachine.request([&]{ tea.prepareReceipe(); });
      coffeeMachine.start();

      coffeeMachine.request([&]{ milkFoam.makeFoam(200); });
      coffeeMachine.request([&]{ milkFoam.makeFoam(300); });
      coffeeMachine.start();

      function<string()> condimentDescription;
      condimentDescription = [=] { return accu<string>(&Milk::description, condimentDescription); };
      condimentDescription = [=] { return accu<string>(&Sugar::description, condimentDescription); };
      condimentDescription = [=] { return accu<string>(&Sugar::description, condimentDescription); };

      function<float()> condimentPrice;
      condimentPrice = [=] { return accu<float>(&Milk::price, condimentPrice); };
      condimentPrice = [=] { return accu<float>(&Sugar::price, condimentPrice); };
      condimentPrice = [=] { return accu<float>(&Sugar::price, condimentPrice); };

      cout << "Condiments: " << condimentDescription() << '\n';
      cout << "Price: " << condimentPrice() << '\n';
    }
#endif
  }

  return 0;
}
