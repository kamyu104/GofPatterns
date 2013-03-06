// /Users/Tobias/Downloads/checker-270/bin/clang++ -std=c++0x -stdlib=libc++ -I./ -I../ -I/Developer/Library/boost_1_51_0 -o app_cpp11 app.cpp
#include <CaffeineBeverage.h>
#include <Recipes.h>
#include <CoffeeMachine.h>
#include <View.h>
#include <MilkFoam.h>
#include <accu.h>
#include <Milk.h>
#include <Sugar.h>
#include <BeverageFactory.h>
#include <Condiment.h>
#include <CondimentFactory.h>

#include <functional>
#include <vector>
#include <memory>

// Boost.Signals2 tutorial
#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
  using namespace boost::signals2;

  void hello() 
  { 
    std::cout << "Hello "; 
  } 
  
  struct World
  {
    void operator()()
    {
      std::cout << "World";
    }
  };

  struct CoutChar
  {
    CoutChar(char c)
      : letter(c)
    {}

    void print()
    {
      std::cout << letter;
    }

    char letter;
  };

  int main() 
  { 
    World world;
    CoutChar c('!');
    signal<void ()> s;
 
    s.connect(&hello);
    s.connect(world);
    s.connect(std::bind(&CoutChar::print, c)); 
    s(); 

/*
  Hello World!
*/

    s.disconnect_all_slots();
    s.connect(1, world);
    s.connect(0, &hello);
    s.connect(2, std::bind(&CoutChar::print, c)); 
    s(); 

/*
  Hello World!
*/

    s.disconnect_all_slots();
    s.connect(1, world);
    s.connect(0, &hello);
    {
      boost::shared_ptr<CoutChar> c(new CoutChar('!'));
      s.connect(2, signal<void()>::slot_type(&CoutChar::print, c.get()).track(c));
      std::cout << s.num_slots();
    }
    s(); 
    std::cout << s.num_slots();
  }
/*
int main(int argc, char* argv[])
{
  using namespace std;
  using namespace cpp11;
  { // bind
    using Beverages = std::vector<std::unique_ptr<CaffeineBeverage>>;
    Beverages beverages;
    CoffeeMachine coffeeMachine;
    View view;
    BeverageFactory beverageFactory;

    coffeeMachine.getNotifiedOnFinished(bind(&View::coffeeMachineFinished, &view));
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
	    condiments.description = bind(&accu<string>, condiment.description, condiments.description);
	    condiments.price = bind(&accu<float>, condiment.price, condiments.price);
	  } while(true);
	beverages.back()->condiments(condiments);
      } while(true);
    if(!beverages.empty())
      {
	for(auto& beverage : beverages)
	  {
	    coffeeMachine.request(bind(&CaffeineBeverage::prepare, &(*beverage)));
	  }
	coffeeMachine.start();
	for(auto& beverage : beverages)
	  {
	    beverage->description();
	    beverage->price();
	  }
      }
  }
  { // lambda
    using Beverages = std::vector<std::unique_ptr<CaffeineBeverage>>;
    Beverages beverages;
    CoffeeMachine coffeeMachine;
    View view;
    BeverageFactory beverageFactory;

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
	    condiments.description = [=]{ return accu(condiment.description, condiments.description); };
	    condiments.price = [=]{ return accu(condiment.price, condiments.price); };
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

  using Beverages = std::vector<std::unique_ptr<CaffeineBeverage>>;
  Beverages beverages;
  CoffeeMachine coffeeMachine;
  View view;
  BeverageFactory beverageFactory;

  auto start = std::chrono::high_resolution_clock::now();

  for(int i = 0; i < 10; ++i)
    {
      beverages.emplace_back(beverageFactory.create("Coffee"));
      Condiment condiments;
      for(int i = 0; i < 10; ++i)
	{
	  CondimentFactory condimentFactory;
	  Condiment condiment = condimentFactory.create("Milk");
	  condiments.description = [=]{ return accu(condiment.description, condiments.description); };
	  condiments.price = [=]{ return accu(condiment.price, condiments.price); };
	}
      beverages.back()->condiments(condiments);
    }
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

  auto end = std::chrono::high_resolution_clock::now();

  auto elapsed = end - start;
  std::cout << elapsed.count() << '\n';
  std::string dummy;
  view.askForCondiments(dummy);
}
*/
