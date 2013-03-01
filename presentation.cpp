/* color theme white bg = JB Simple  font size = 18 */
    // Strategy
    // classic

    class Recipe
    {
      virtual int amountWaterMl() = 0;
      virtual void brew() = 0;
    };

    class CaffeineBeverage
    {
      void prepare()
      {
	boilWater(recipe.amountWaterMl());
	recipe.brew();
	pourInCup();
      }
    };

    class CoffeeRecipe : public Recipe
    {
      CoffeeRecipe(int amountWaterMl)
        : Recipe()
	, amountWaterMl(amountWaterMl)
      {}

      virtual void brew() { std::cout << "dripping Coffee through filter\n"; }

      virtual int amountWaterMl() { return amountWaterMl; }
    };

    class TeaRecipe : public Recipe
    {
      TeaRecipe(int amountWaterMl)
        : Recipe()
        , amountWaterMl(amountWaterMl)
      {}

      virtual void brew() { std::cout << "steeping Tea\n"; }

      virtual int amountWaterMl() { return amountWaterMl; }
    };

    CoffeeRecipe coffeeRecipe(150);
    TeaRecipe teaRecipe(200);
    CaffeineBeverage coffee(coffeeRecipe);
    CaffeineBeverage tea(teaRecipe);

    typedef vector<CaffeineBeverage*> Beverages;
    Beverages beverages;

    beverages.push_back(&coffee);
    beverages.push_back(&tea);

    for(Beverages::iterator it(beverages.begin()); it != beverages.end(); ++it)
    {
      (*it)->prepare();
    }

/*
    boiling 150ml water
    dripping Coffee through filter
    pour in cup
    boiling 200ml water
    steeping Tea
    pour in cup
*/
    // Strategy
    // cpp11

  class CaffeineBeverage
  {
    CaffeineBeverage(std::function<int()> amountWaterMl, std::function<void()> brew)
      : brew(brew)
      , amountWaterMl(amountWaterMl)
      {}

    void prepare() const
    {
      boilWater(amountWaterMl());
      brew();
      pourInCup();
    }
  };

  static void brewCoffee() { std::cout << "dripping Coffee through filter\n"; }

  static void brewTea() { std::cout << "steeping Tea\n"; }

  static int amountWaterMl(int ml) { return ml; }

      CaffeineBeverage coffee(
        bind(&Recipes::amountWaterMl, 150), &Recipes::brewCoffee);
      CaffeineBeverage tea(
        bind(&Recipes::amountWaterMl, 200), &Recipes::brewTea);

      typedef vector<CaffeineBeverage*> Beverages;
      Beverages beverages;
      beverages.push_back(&coffee);
      beverages.push_back(&tea);

      for_each(
        begin(beverages), end(beverages),
        bind(&CaffeineBeverage::prepare, placeholders::_1));
/*
    boiling 150ml water
    dripping Coffee through filter
    pour in cup
    boiling 200ml water
    steeping Tea
    pour in cup
*/
      CaffeineBeverage coffee(
        []{ return Recipes::amountWaterMl(150); }, &Recipes::brewCoffee);
      CaffeineBeverage tea(
        []{ return Recipes::amountWaterMl(200); }, &Recipes::brewTea);

      using Beverages = vector<CaffeineBeverage*>;
      Beverages beverages;
      beverages.push_back(&coffee);
      beverages.push_back(&tea);

      for(auto beverage : beverages){ beverage->prepare(); }
/*
    boiling 150ml water
    dripping Coffee through filter
    pour in cup
    boiling 200ml water
    steeping Tea
    pour in cup
*/
    // Command
    // classic

    class Order
    {
      virtual void execute() = 0;
    };

    class MakeCaffeineBeverage : public Order
    {
      MakeCaffeineBeverage(CaffeineBeverage& beverage)
      : Order()
      , beverage(beverage)
      {}

      virtual void execute()
      {
	beverage.prepare();
      }
    };

  class CoffeeMachine
  {
    typedef std::vector<Order*> OrderQ;
    OrderQ orders;

    CoffeeMachine()
      : orders()
    {}

    void request(Order* order)
    {
      orders.push_back(order);
    }

    void start()
    {
      for(CommandQ::iterator it(orders.begin()); it != orders.end(); ++it)
	{
	  (*it)->execute();
	  delete (*it);
	}
      orders.clear();
    }
  };

    CoffeeMachine coffeeMachine;

    coffeeMachine.request(new MakeCaffeineBeverage(coffee));
    coffeeMachine.request(new MakeCaffeineBeverage(tea));
    coffeeMachine.start();

/*
    boiling 150ml water
    dripping Coffee through filter
    pour in cup
    boiling 200ml water
    steeping Tea
    pour in cup
*/
    //cpp11

    class CoffeeMachine
    {
      typedef std::vector<std::function<void()>> OrderQ;

      CoffeeMachine()
	: orders()
      {}

      void request(OrderQ::value_type c)
      {
	orders.push_back(c);
      }

      void start()
      {
	for(auto const& order : orders){ order(); }
      }
    };


      CoffeeMachine coffeeMachine;

      coffeeMachine.request(bind(&CaffeineBeverage::prepare, &coffee));
      coffeeMachine.request(bind(&CaffeineBeverage::prepare, &tea));
      coffeeMachine.start();

/*
boiling 150ml water
dripping Coffee through filter
pour in cup
boiling 200ml water
steeping Tea
pour in cup
*/
      CoffeeMachine coffeeMachine;

      coffeeMachine.request([&]{ coffee.prepare(); });
      coffeeMachine.request([&]{ tea.prepare(); });
      coffeeMachine.start();
/*
boiling 150ml water
dripping Coffee through filter
pour in cup
boiling 200ml water
steeping Tea
pour in cup
*/

// Order Mikfoam classic

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
	std::cout << "boiling " << mlMilk << "ml milk\n";
      }

      void pourInCup()
      {
	std::cout << "pour in cup\n";
      }

      void foaming()
      {
	std::cout << "foaming\n";
      }
    };

    class MakeMilkFoam : public Order
    {
    public:
      MakeMilkFoam(MilkFoam& milk, int mlMilk)
	: Order()
	, milk(milk)
	, mlMilk(mlMilk)
      {}

      virtual void execute()
      {
	milk.makeFoam(mlMilk);
      }

      void setMlMilk(int mlMilk)
      {
	mlMilk = mlMilk;
      }

    private:
      MilkFoam& milk;
      int mlMilk;
    };

    MilkFoam milkFoam;
    MakeMilkFoam makeMilkFoam(milkFoam, 100);
    CoffeeMachine coffeeMachine;

    coffeeMachine.request(&makeMilkFoam);
    coffeeMachine.start();

    makeMilkFoam.setMlMilk(200);
    coffeeMachine.request(&makeMilkFoam);
    makeMilkFoam.setMlMilk(300);
    coffeeMachine.request(&makeMilkFoam);
    coffeeMachine.start();

/*

boiling 100ml milk
pour in cup
foaming
boiling 300ml milk
pour in cup
foaming
boiling 300ml milk
pour in cup
foaming
boiling 300ml milk
pour in cup
foaming

*/

// Order MilkFoam cpp11 bind

      MilkFoam milkFoam;
      coffeeMachine.request(bind(&MilkFoam::makeFoam, &milkFoam, 100));
      coffeeMachine.start();

      coffeeMachine.request(bind(&MilkFoam::makeFoam, &milkFoam, 200));
      coffeeMachine.request(bind(&MilkFoam::makeFoam, &milkFoam, 300));
      coffeeMachine.start();

// Order MilkFoam cpp11 lambda
      MilkFoam milkFoam;
      coffeeMachine.request([&]{ milkFoam.makeFoam(100); });
      coffeeMachine.start();

      coffeeMachine.request([&]{ milkFoam.makeFoam(200); });
      coffeeMachine.request([&]{ milkFoam.makeFoam(300); });
      coffeeMachine.start();

/*

boiling 100ml milk
pour in cup
foaming
boiling 200ml milk
pour in cup
foaming
boiling 300ml milk
pour in cup
foaming

*/

// Chain
// classic

    class Condiment
    {
      Condiment(Condiment* next)
      : next(next)
      {}

      std::string description()
      {
	if(next) return this->onDescription() + next->description();
	return this->onDescription();
      }

      float price()
      {
	if(next) return this->onPrice() + next->price();
	return this->onPrice();
      }

      virtual std::string onDescription() = 0;
      virtual float onPrice() = 0;
    };

    class Sugar : public Condiment
    {
      Sugar(Condiment* next)
      : Condiment(next)
      {}

      virtual std::string onDescription() { return "-Sugar-"; }

      virtual float onPrice() {	return 0.07f; }
    };

    class Milk : public Condiment
    {
      Milk(Condiment* next)
      : Condiment(next)
      {}

      virtual std::string onDescription() { return "-Milk-"; }

      virtual float onPrice() {	return 0.13f; }
    };

    Condiment* milk = new Milk();
    Condiment* sugarMilk = new Sugar(milk);
    Condiment* doubleSugarMilk = new Sugar(sugarMilk);

    cout << "Condiments: " << doubleSugarMilk->description() << '\n';
    cout << "Price: " << doubleSugarMilk->price() << '\n';

/*
  Condiments: -Sugar--Sugar--Milk-
  Price: 0.27
*/

// Chain
// cpp11

  struct Condiment
  {
    std::function<std::string()> description;
    std::function<float()> price;
  };

  class Sugar
  {
  public:
    static std::string description()
    {
      return "-Sugar-";
    }

    static float price()
    {
      return 0.07f;
    }
  };

  class Milk
  {
  public:
    static std::string description()
    {
      return "-Milk-";
    }

    static float price()
    {
      return 0.13f;
    }
  };

  template<typename Res>
  static Res accu(std::function<Res()> call, std::function<Res()> next)
  {
    if(next) return call() + next();
    return call();
  }

      Condiment condiments;
      condiments.description = bind(&accu<string>, &Milk::description, condiments.description);
      condiments.description = bind(&accu<string>, &Sugar::description, condiments.description);
      condiments.description = bind(&accu<string>, &Sugar::description, condiments.description);

      condiments.price = bind(&accu<float>, &Milk::price, condiments.price);
      condiments.price = bind(&accu<float>, &Sugar::price, condiments.price);
      condiments.price = bind(&accu<float>, &Sugar::price, condiments.price);

      cout << "Condiments: " << condiments.description() << '\n';
      cout << "Price: " << condiments.price() << '\n';

  template<typename Call, typename NextCall>
  static auto accu(Call call, NextCall next) -> decltype(call() + next())
  {
    if(next) return call() + next();
    return call();
  }
      Condiment condiments;
      condiments.description = [=] { return accu(&Milk::description, condiments.description); };
      condiments.description = [=] { return accu(&Sugar::description, condiments.description); };
      condiments.description = [=] { return accu(&Sugar::description, condiments.description); };

      condiments.price = [=] { return accu(&Milk::price, condiments.price); };
      condiments.price = [=] { return accu(&Sugar::price, condiments.price); };
      condiments.price = [=] { return accu(&Sugar::price, condiments.price); };

      cout << "Condiments: " << condiments.description() << '\n';
      cout << "Price: " << condiments.price() << '\n';

/*
  Condiments: -Sugar--Sugar--Milk-
  Price: 0.27
*/

// Observer
// classic

    class Observer
    {
      virtual void notify() = 0;
    };

    class Observable
    {
      void addObserver(Observers::value_type o)
      {
	Observers::iterator it = std::find(observers.begin(), observers.end(), o);
	if(it == observers.end()) observers.push_back(o);
      }

      void removeObserver(Observers::value_type o)
      {
	Observers::iterator it = std::find(observers.begin(), observers.end(), o);
	if(it != observers.end()) observers.erase(it);
      }

      void notify()
      {
	for(Observers::iterator it(observers.begin()); it != observers.end(); ++it)
	  {
	    (*it)->notify();
	  }
      }
    };

  class CoffeeMachine : public Observable
  {
    void start()
    {
      for(CommandQ::iterator it(commands.begin()); it != commands.end(); ++it)
	{
	  (*it)->execute();
	  delete (*it);
	}
      commands.clear();
      this->notifyFinished();
    }
  };

    class View : public Observer
    {
      View()
	: Observer()
      {}

      virtual void notify()
      {
	std::cout << "Orders are ready to be served\n";
      }
    };

    CoffeeMachine coffeeMachine;
    View view;

    coffeeMachine.addObserver(&view);

    coffeeMachine.request(new MakeCaffeineBeverage(coffee));
    coffeeMachine.request(new MakeCaffeineBeverage(tea));
    coffeeMachine.start();

/*
  boiling 150ml water
  dripping Coffee through filter
  pour in cup
  boiling 200ml water
  steeping Tea
  pour in cup
  Orders are ready to be served
*/

// Observer
// boost.signals2

  class CoffeeMachine
  {
    void start()
    {
      for(auto const& cmd : commands){ cmd(); }
      commands.clear();
      sigFinished();
    }

    void getNotifiedOnFinished(std::function<void()> callback)
    {
      sigFinished.connect(callback);
    }

    boost::signals2::signal_type<void(), boost::signals2::keywords::mutex_type<
	boost::signals2::dummy_mutex>>::type sigFinished;
  };

  class View
  {
    void coffeeMachineFinished()
    {
      std::cout << "Orders are ready to be served\n";
    }
  };

      CoffeeMachine coffeeMachine;
      View view;
      coffeeMachine.getNotifiedOnFinished(bind(&View::coffeeMachineFinished, &view));

      coffeeMachine.request(bind(&CaffeineBeverage::prepare, &coffee));
      coffeeMachine.request(bind(&CaffeineBeverage::prepare, &tea));
      coffeeMachine.start();

      CoffeeMachine coffeeMachine;
      View view;
      coffeeMachine.getNotifiedOnFinished([&]{ view.coffeeMachineFinished(); });

      coffeeMachine.request([&]{ coffee.prepare(); });
      coffeeMachine.request([&]{ tea.prepare(); });
      coffeeMachine.start();

/*
  boiling 150ml water
≤≤  dripping Coffee through filter
  pour in cup
  boiling 200ml water
  steeping Tea
  pour in cup
  Orders are ready to be served
*/

// Factory
// classic

    class CaffeineBeverageFactory
    {
      virtual CaffeineBeverage* create() = 0;
    };

    class CoffeeFactory : public CaffeineBeverageFactory
    {
      virtual CaffeineBeverage* create()
      {
	return new Coffee();
      }
    };

    class TeaFactory : public CaffeineBeverageFactory
    {
      virtual CaffeineBeverage* create()
      {
	return new Tea();
      }
    };

    class Coffee : public CaffeineBeverage
    {
      Coffee()
	: CaffeineBeverage(recipe)
	, recipe(125)
      {}

      CoffeeRecipe recipe;
    };

    class Tea : public CaffeineBeverage
    {
      Tea()
	: CaffeineBeverage(recipe)
	, recipe(200)
      {}

      TeaRecipe recipe;
    };

    class BeverageFactory
    {
      BeverageFactory()
	: factory()
      {
	factory["Coffee"] = new CoffeeFactory();
	factory ["Tea"] = new TeaFactory();
      }

      ~BeverageFactory()
      {
	delete factory["Coffee"];
	delete factory["Tea"];
      }

      CaffeineBeverage* create(std::string const& beverage)
      {
	return factory[beverage]->create();
      }

      std::map<std::string, CaffeineBeverageFactory*> factory;
    };

    BeverageFactory factory;
    CaffeineBeverage* b1 = factory.create("Coffee");
    CaffeineBeverage* b2 = factory.create("Tea");

    b1->prepare();
    b2->prepare();

    delete b1;
    delete b2;

/*
  boiling 150ml water
  dripping Coffee through filter
  pour in cup
  boiling 200ml water
  steeping Tea
  pour in cup
*/

// factory
// boost.functional.factory

  class BeverageFactory
  {
    BeverageFactory()
      : factory()
    {
      factory["Coffee"] =
        std::bind(
  		boost::factory<CaffeineBeverage*>(),
  		std::function<int ()>(std::bind(&Recipes::amountWaterMl, 150)),
  		&Recipes::brewCoffee);
  
      factory["Tea"] =
        std::bind(
  		boost::factory<CaffeineBeverage*>(),
  		std::function<int ()>(std::bind(&Recipes::amountWaterMl, 200)),
  		&Recipes::brewTea);
    }
  
    std::unique_ptr<CaffeineBeverage> create(std::string const& beverage)
    {
      return std::unique_ptr<CaffeineBeverage>(factory[beverage]());
    }
  
    std::map<std::string, std::function<CaffeineBeverage*()>> factory;
  };

  class BeverageFactory
  {
    BeverageFactory()
      : factory()
    {
      factory["Coffee"] = []
        {
  	return new CaffeineBeverage(
  				    []{ return 150; },
  				    &Recipes::brewCoffee);
        };
  
      factory["Tea"] = []
        {
  	return new CaffeineBeverage(
  				    [] { return 200; },
  				    &Recipes::brewTea);
        };
    }
  
    std::unique_ptr<CaffeineBeverage> create(std::string const& beverage)
    {
      return std::unique_ptr<CaffeineBeverage>(factory[beverage]());
    }
  
    std::map<std::string, std::function<CaffeineBeverage*()>> factory;
  };

      BeverageFactory factory;
      factory.create("Coffee")->prepare();
      factory.create("Tea")->prepare();

    // patterns for communication

  struct Recipe
  {
    std::function<void()> brew;
    std::function<void()> addCondiments;
  };

    // Milkfoam
    // classic

    class MilkFoam
    {
      void makeFoam(int mlMilk)
      {
	boilMilk(mlMilk);
	pourInCup();
	foaming();
      }

      void boilMilk(int mlMilk)
      {
	std::cout << "boiling " << mlMilk << "ml milk\n";
      }

      void pourInCup()
      {
	std::cout << "pour in cup\n";
      }

      void foaming()
      {
	std::cout << "foaming\n";
      }
    };

    class MakeMilkFoam : public Command
    {
      MakeMilkFoam(MilkFoam& milk, int mlMilk)
	: Command()
	, milk(milk)
	, mlMilk(mlMilk)
      {}

      virtual void execute()
      {
	milk.makeFoam(mlMilk);
      }

      void amountMl(int ml)
      {
	mlMilk = ml;
      }

    private:
      MilkFoam& milk;
      int mlMilk;
    };

    CoffeeMachine coffeeMachine;
    MilkFoam milkFoam;
    MakeMilkFoam makeMilkFoam(milkFoam, 100);

    coffeeMachine.request(&makeMilkFoam);
    makeMilkFoam.amountMl(200);
    coffeeMachine.request(&makeMilkFoam);
    makeMilkFoam.amountMl(300);
    coffeeMachine.request(&makeMilkFoam);
    coffeeMachine.start();
/*
   boiling 300ml milk
   pour in cup
   foaming
   patterns_clang(13032) malloc: *** error for object 0x7fff686f6660: pointer being freed was not allocated
   *** set a breakpoint in malloc_error_break to debug
   Abort trap: 6
*/

    coffeeMachine.request(new MakeMilkFoam(milkFoam, 100));
    coffeeMachine.request(new MakeMilkFoam(milkFoam, 200));
    coffeeMachine.request(new MakeMilkFoam(milkFoam, 300));
    coffeeMachine.start();

    // MilkFoam
    // cpp11

    class MilkFoam
    {
      void makeFoam(int mlMilk)
      {
	boilMilk(mlMilk);
	pourInCup();
	foaming();
      }

      void boilMilk(int mlMilk)
      {
	std::cout << "boiling " << mlMilk << "ml milk\n";
      }

      void pourInCup()
      {
	std::cout << "pour in cup\n";
      }

      void foaming()
      {
	std::cout << "foaming\n";
      }
    };

      MilkFoam milkFoam;
      coffeeMachine.request([&]{ milkFoam.makeFoam(100); });
      coffeeMachine.request([&]{ milkFoam.makeFoam(200); });
      coffeeMachine.request([&]{ milkFoam.makeFoam(300); });
      coffeeMachine.start();

// App classic

  typedef std::vector<CaffeineBeverage*> Beverages;
  Beverages beverages;
  coffeeMachine.addObserver(&view);
  do
    {
      std::string inBeverage;
      if(!view.askForBeverage(inBeverage)) break;
      beverages.push_back(beverageFactory.create(inBeverage));
      CondimentFactory condimentFactory;
      Condiment* condiments = 0;
      do
	{
	  std::string inCondiment;
	  if(!view.askForCondiments(inCondiment)) break;
	  condiments = condimentFactory.create(inCondiment, condiments);
	} while(true);
      beverages.back()->condiments(condiments);
    } while(true);

  if(!beverages.empty())
    {
      for(Beverages::iterator it(beverages.begin()); it != beverages.end(); ++it)
	{
	  coffeeMachine.request(new MakeCaffeineBeverage(**it));
	}
      coffeeMachine.start();
      do
	{
	  beverages.back()->description();
	  beverages.back()->price();
	  delete beverages.back();
	  beverages.pop_back();
	} while(!beverages.empty());
    }

/*
  Coffeemachine now ready for taking orders or q for quit!
  Coffee
  Choose condiments or q for next beverage order:
  Sugar
  Choose condiments or q for next beverage order:
  Sugar
  Choose condiments or q for next beverage order:
  Milk
  Choose condiments or q for next beverage order:
  q
  Coffeemachine now ready for taking orders or q for quit!
  Tea
  Choose condiments or q for next beverage order:
  Milk
  Choose condiments or q for next beverage order:
  Milk
  Choose condiments or q for next beverage order:
  q
  Coffeemachine now ready for taking orders or q for quit!
  q

  boiling 125ml water
  dripping Coffee through filter
  pour in cup
  -Milk--Sugar--Sugar-
  boiling 200ml water
  steeping Tea
  pour in cup
  -Milk--Milk-
  Orders are ready to be served
  Tea : -Milk--Milk-
  1.53
  Coffee : -Milk--Sugar--Sugar-
  3.25
*/

// app cpp11 lambda

    using Beverages = std::vector<std::unique_ptr<CaffeineBeverage>>;
    Beverages beverages;
    coffeeMachine.getNotifiedOnFinished([&]{ view.coffeeMachineFinished(); });
    do
      {
	std::string inBeverage;
	if(!view.askForBeverage(inBeverage)) break;
	beverages.emplace_back(beverageFactory.create(inBeverage));
	Condiment condiments;
	do
	  {
	    CondimentFactory condimentFactory;
	    std::string inCondiment;
	    if(!view.askForCondiments(inCondiment)) break;
	    Condiment condiment = condimentFactory.create(inCondiment);
	    condiments.description = [=]{
	      return accu(condiment.description, condiments.description); };
	    condiments.price = [=]{
	      return accu(condiment.price, condiments.price); };
	  } while(true);
	beverages.back()->condiments(condiments);
      } while(true);

    if(!beverages.empty())
      {
	for(auto& beverage : beverages)
	  {
	    coffeeMachine.request([&]{ beverage->prepare(); });
	  }
	coffeeMachine.start();
	for(auto& beverage : beverages)
	  {
	    beverage->description();
	    beverage->price();
	  }
      }
  }

/*
  Coffeemachine now ready for taking orders or q for quit!
  Coffee
  Choose condiments or q for next beverage order:
  Milk
  Choose condiments or q for next beverage order:
  Sugar
  Choose condiments or q for next beverage order:
  q
  Coffeemachine now ready for taking orders or q for quit!
  Tea
  Choose condiments or q for next beverage order:
  Milk
  Choose condiments or q for next beverage order:
  Milk
  Choose condiments or q for next beverage order:
  q
  Coffeemachine now ready for taking orders or q for quit!
  q

  boiling 125ml water
  dripping Coffee through filter
  pour in cup
  -Sugar--Milk-
  boiling 200ml water
  steeping Tea
  pour in cup
  -Milk--Milk-
  Orders are ready to be served
  Coffee : -Sugar--Milk-
  2.68
  Tea : -Milk--Milk-
  1.53
*/
