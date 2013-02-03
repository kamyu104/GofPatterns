// /Users/Tobias/Downloads/checker-270/bin/clang++ -std=c++0x -stdlib=libc++ -I./ -I/Developer/Library/boost_1_51_0 -o patterns_clang patterns.cpp

// /Users/Tobias/Downloads/checker-270/scan-build -V -o ./scan /Users/Tobias/Downloads/checker-270/bin/clang++ -std=c++0x -stdlib=libc++ -I./ -I/Developer/Library/boost_1_51_0 -o patterns_clang patterns.cpp


// g++ --std=C++0x -o patterns_gcc patterns.cpp

// D:\Projects\C++\gcc_4.7_20110903\bin\g++.exe --std=c++0x patterns.cpp -o patterns_gcc

// D:\Projects\C++\llvm\build\bin\Debug\clang++ -std=c++0x -stdlib=libc++ -o patterns_clang patterns.cpp

// "C:\Program Files\Microsoft Visual Studio 10.0\VC\bin\vcvars32.bat" & "C:\Program Files\Microsoft Visual Studio 10.0\VC\bin\cl.exe" /EHsc /nologo /W4 /NTd patterns.cpp

#include <classic/CoffeeReceipe.h>
#include <classic/TeaReceipe.h>
#include <classic/CaffeineBeverage.h>
#include <classic/MakeCaffeineDrink.h>
#include <classic/MilkFoam.h>
#include <classic/MakeMilkFoam.h>
#include <classic/CoffeeMachine.h>
#include <classic/View.h>
#include <classic/Milk.h>
#include <classic/Sugar.h>
#include <classic/BeverageFactory.h>

#include <cpp11/CaffeineBeverage.h>
#include <cpp11/Receipes.h>
#include <cpp11/CoffeeMachine.h>
#include <cpp11/View.h>
#include <cpp11/MilkFoam.h>
#include <cpp11/accu.h>
#include <cpp11/Milk.h>
#include <cpp11/Sugar.h>
#include <cpp11/BeverageFactory.h>

#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include <map>

using namespace std;

int main(int argc, char* argv[])
{
  {
    using namespace classic;
    
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

    BeverageFactory factory;
    factory.create("Coffee")->prepareReceipe();
    factory.create("Tea")->prepareReceipe();
  }

  {
    {
      using namespace cpp11;

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

      BeverageFactory factory;
      factory.create("Coffee")->prepareReceipe();
      factory.create("Tea")->prepareReceipe();
    }

#if defined(__GNUC__) || defined(__clang__)
    {
      using namespace cpp11;

      CaffeineBeverage coffee([]{ Receipes::brewCoffee(1); }, []{ Receipes::addSugarAndMilk(); });
      CaffeineBeverage tea([]{ Receipes::brewTea(2); }, []{ Receipes::addLemon(); });

      typedef vector<CaffeineBeverage*> Beverages;
      Beverages beverages;

      beverages.push_back(&coffee);
      beverages.push_back(&tea);

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
