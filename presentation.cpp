/* color theme white bg = JB Simple  font size = 18 */
    // Strategy
    // classic

    class Receipe
    {
      virtual int amountWaterMl() = 0;
      virtual void brew() = 0;
    };

    class CaffeineBeverage
    {
      CaffeineBeverage(Receipe& receipe)
        : m_receipe(receipe)
      {}

      void prepareReceipe()
      {
	boilWater(m_receipe.amountWaterMl());
	m_receipe.brew();
	pourInCup();
      }
    };

    class CoffeeReceipe : public Receipe
    {
      CoffeeReceipe(int amountWaterMl)
        : Receipe()
	, m_amountWaterMl(amountWaterMl)
      {}

      virtual void brew()
      {
	std::cout << "dripping Coffee"
                     "through filter\n";
      }

      virtual int amountWaterMl()
      {
	return m_amountWaterMl;
      }
    };

    class TeaReceipe : public Receipe
    {
      TeaReceipe(int amountWaterMl)
        : Receipe()
        , m_amountWaterMl(amountWaterMl)
      {}

      virtual void brew()
      {
	std::cout << "steeping Tea\n";
      }

      virtual int amountWaterMl()
      {
	return m_amountWaterMl;
      }
    };

    CoffeeReceipe coffeeReceipe(150);
    TeaReceipe teaReceipe(200);
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
    CaffeineBeverage(
      std::function<int()> amountWaterMl,
      std::function<void()> brew)
      : m_brew(brew)
      , m_amountWaterMl(amountWaterMl)
      {}

    void prepareReceipe() const
    {
      boilWater(m_amountWaterMl());
      m_brew();
      pourInCup();
    }
  };

  class Receipes
  {
    static void brewCoffee()
    {
      std::cout << "dripping Coffee "
                   "through filter\n";
    }

    static void brewTea()
    {
      std::cout << "steeping Tea\n";
    }

    static int amountWaterMl(int ml)
    {
      return ml;
    }
  };

      CaffeineBeverage coffee(
        bind(&Receipes::amountWaterMl, 150), &Receipes::brewCoffee);
      CaffeineBeverage tea(
        bind(&Receipes::amountWaterMl, 200), &Receipes::brewTea);

      typedef vector<CaffeineBeverage*> Beverages;
      Beverages beverages;
      beverages.push_back(&coffee);
      beverages.push_back(&tea);

      for_each(
        begin(beverages), end(beverages),
        bind(&CaffeineBeverage::prepareReceipe, placeholders::_1));
/*
    boiling 150ml water
    dripping Coffee through filter
    pour in cup
    boiling 200ml water
    steeping Tea
    pour in cup
*/
      CaffeineBeverage coffee(
        []{ return Receipes::amountWaterMl(150); }, &Receipes::brewCoffee);
      CaffeineBeverage tea(
        []{ return Receipes::amountWaterMl(200); }, &Receipes::brewTea);

      using Beverages = vector<CaffeineBeverage*>;
      Beverages beverages;
      beverages.push_back(&coffee);
      beverages.push_back(&tea);

      for(auto beverage : beverages){ beverage->prepareReceipe(); }
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
      MakeCaffeineBeverage(CaffeineBeverage& drink)
      : Order()
      , m_drink(drink)
      {}

      virtual void execute()
      {
	m_drink.prepareReceipe();
      }
    };

  class CoffeeMachine
  {
    typedef std::vector<Order*> OrderQ;

    CoffeeMachine()
      : m_orders()
    {}

    void request(Order* c)
    {
      m_orders.push_back(c);
    }

    void start()
    {
      for(CommandQ::iterator it(m_orders.begin()); it != m_orders.end(); ++it)
	{
	  (*it)->execute();
	  delete (*it);
	}
      m_orders.clear();
    }
  };

    CoffeeMachine coffeeMachine;

    coffeeMachine.request(new MakeCaffeineDrink(coffee));
    coffeeMachine.request(new MakeCaffeineDrink(tea));
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
	: m_orders()
      {}

      void request(OrderQ::value_type c)
      {
	m_orders.push_back(c);
      }

      void start()
      {
	for(auto const& order : m_orders){ order(); }
      }
    };


      CoffeeMachine coffeeMachine;

      coffeeMachine.request(bind(&CaffeineBeverage::prepareReceipe, &coffee));
      coffeeMachine.request(bind(&CaffeineBeverage::prepareReceipe, &tea));
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

      coffeeMachine.request([&]{ coffee.prepareReceipe(); });
      coffeeMachine.request([&]{ tea.prepareReceipe(); });
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
      : m_next(next)
      {}

      std::string description()
      {
	if(m_next) return this->onDescription() + m_next->description();
	return this->onDescription();
      }

      float price()
      {
	if(m_next) return this->onPrice() + m_next->price();
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

      virtual std::string onDescription()
      {
	return "-Sugar-";
      }

      virtual float onPrice()
      {
	return 0.07f;
      }
    };

    class Milk : public Condiment
    {
      Milk(Condiment* next)
      : Condiment(next)
      {}

      virtual std::string onDescription()
      {
	return "-Milk-";
      }

      virtual float onPrice()
      {
	return 0.13f;
      }
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
