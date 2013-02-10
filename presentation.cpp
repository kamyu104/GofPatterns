
    // Strategy
    // classic

    class Receipe
    {
    public:
      virtual int amountWaterMl() = 0;
      virtual void brew() = 0;
    };

    class CaffeineBeverage
    {
    public:
      CaffeineBeverage(Receipe& receipe)
      : m_receipe(receipe)
      {}

      void prepareReceipe()
      {
	boilWater(m_receipe.amountWaterMl());
	m_receipe.brew();
	pourInCup();
      }

    private:
      Receipe& m_receipe;
    };

    class CoffeeReceipe : public Receipe
    {
    public:
      CoffeeReceipe(int amountWaterMl)
        : Receipe()
	, m_amountWaterMl(amountWaterMl)
      {}

      virtual void brew()
      {
	std::cout << "dripping Coffee through filter\n";
      }

      virtual int amountWaterMl()
      {
	return m_amountWaterMl;
      }

    private:
      int m_amountWaterMl;

      NO_COPY(CoffeeReceipe);
    };

    class TeaReceipe : public Receipe
    {
    public:
      TeaReceipe(int amountWaterMl)
        : Receipe()
        , m_amountWaterMl(amountWaterMl)
      {}

      virtual void brew()
      {
	std::cout << "steeping Tea through filter\n";
      }

      virtual int amountWaterMl()
      {
	return m_amountWaterMl;
      }

    private:
      int m_amountWaterMl;

      NO_COPY(TeaReceipe);
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
  public:
  CaffeineBeverage(std::function<int()> amountWaterMl, std::function<void()> brew)
    : m_brew(brew)
      , m_amountWaterMl(amountWaterMl)
      {}

    void prepareReceipe() const
    {
      boilWater(m_amountWaterMl());
      m_brew();
      pourInCup();
    }

  private:
    void boilWater(int amountWaterMl) const
    {
      std::cout << "boiling " << amountWaterMl << "ml water\n";
    }

    void pourInCup() const
    {
      std::cout << "pour in cup\n";
    }

    std::function<void()> m_brew;
    std::function<int()> m_amountWaterMl;
  };

  class Receipes
  {
  public:
    static void brewCoffee()
    {
      std::cout << "dripping Coffee through filter\n";
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

      CaffeineBeverage coffee(bind(&Receipes::amountWaterMl, 150), &Receipes::brewCoffee);
      CaffeineBeverage tea(bind(&Receipes::amountWaterMl, 200), &Receipes::brewTea);

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
      CaffeineBeverage coffee([]{ return Receipes::amountWaterMl(150); }, []{ Receipes::brewCoffee(); });
      CaffeineBeverage tea([]{ return Receipes::amountWaterMl(200); }, []{ Receipes::brewTea(); });

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

    class Command
    {
    public:
      virtual void execute() = 0;
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
    };

  class CoffeeMachine
  {
  private:
    typedef std::vector<Command*> CommandQ;

  public:
  CoffeeMachine()
    : m_commands()
      {}

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
    }

  private:
    CommandQ m_commands;
  };

    MakeCaffeineDrink makeCoffee(coffee);
    MakeCaffeineDrink makeTea(tea);
    CoffeeMachine coffeeMachine;

    coffeeMachine.request(&makeCoffee);
    coffeeMachine.request(&makeTea);
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
    private:
      typedef std::vector<std::function<void()>> CommandQ;

    public:
      CoffeeMachine()
	: m_commands()
      {}

      void request(CommandQ::value_type c)
      {
	m_commands.push_back(c);
      }

      void start()
      {
	for(auto const& cmd : m_commands){ cmd(); }
      }

    private:
      CommandQ m_commands;
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
