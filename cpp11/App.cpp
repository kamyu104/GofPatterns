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

int main(int argc, char* argv[])
{
  using namespace std;
  using namespace cpp11;
  {
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
}
