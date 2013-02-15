// /Users/Tobias/Downloads/checker-270/bin/clang++ -std=c++0x -stdlib=libc++ -I./ -I/Developer/Library/boost_1_51_0 -o patterns_clang patterns.cpp≥

// /Users/Tobias/Downloads/checker-270/scan-build -V -o ./scan /Users/Tobias/Downloads/checker-270/bin/clang++ -std=c++0x -stdlib=libc++ -I./ -I/Developer/Library/boost_1_51_0 -o patterns_clang patterns.cpp


// g++ --std=C++0x -o patterns_gcc patterns.cpp

// D:\Projects\C++\gcc_4.7_20110903\bin\g++.exe --std=c++0x patterns.cpp -o patterns_gcc

// D:\Projects\C++\llvm\build\bin\Debug\clang++ -std=c++0x -stdlib=libc++ -o patterns_clang patterns.cpp

// "C:\Program Files\Microsoft Visual Studio 10.0\VC\bin\vcvars32.bat" & "C:\Program Files\Microsoft Visual Studio 10.0\VC\bin\cl.exe" /EHsc /nologo /W4 /NTd patterns.cpp

#define _SECURE_SCL 1
#pragma warning(disable:4996)

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
#include <classic/CondimentFactory.h>

#include <cpp11/CaffeineBeverage.h>
#include <cpp11/Receipes.h>
#include <cpp11/CoffeeMachine.h>
#include <cpp11/View.h>
#include <cpp11/MilkFoam.h>
#include <cpp11/accu.h>
#include <cpp11/Milk.h>
#include <cpp11/Sugar.h>
#include <cpp11/BeverageFactory.h>
#include <cpp11/Condiment.h>
#include <cpp11/CondimentFactory.h>

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
    
    cout << "Strategy\n";
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

    cout << "Command\n";
    MilkFoam milkFoam;
    CoffeeMachine coffeeMachine;
    View view;

    coffeeMachine.addObserver(&view);

    coffeeMachine.request(new MakeCaffeineDrink(coffee));
    coffeeMachine.request(new MakeCaffeineDrink(tea));
    coffeeMachine.request(new MakeMilkFoam(milkFoam, 100));
    coffeeMachine.start();
    coffeeMachine.request(new MakeMilkFoam(milkFoam, 200));
    coffeeMachine.request(new MakeMilkFoam(milkFoam, 300));
    coffeeMachine.start();

    Condiment* milk = new Milk();
    Condiment* sugarMilk = new Sugar(milk);
    Condiment* doubleSugarMilk = new Sugar(sugarMilk);

    cout << "Condiments: " << doubleSugarMilk->description() << '\n';
    cout << "Price: " << doubleSugarMilk->price() << '\n';

    BeverageFactory factory;
    CaffeineBeverage* b1 = factory.create("Coffee");
    CaffeineBeverage* b2 = factory.create("Tea");
    b1->prepareReceipe();
    b2->prepareReceipe();
    delete b1;
    delete b2;
  }

  {
    {
      using namespace cpp11;

      cout << "Strategy bind\n";
      CaffeineBeverage coffee(bind(&Receipes::amountWaterMl, 150), &Receipes::brewCoffee);
      CaffeineBeverage tea(bind(&Receipes::amountWaterMl, 200), &Receipes::brewTea);

      typedef vector<CaffeineBeverage*> Beverages;
      Beverages beverages;

      beverages.push_back(&coffee);
      beverages.push_back(&tea);

      for_each(
	       begin(beverages), end(beverages),
	       bind(&CaffeineBeverage::prepareReceipe, placeholders::_1));

      cout << "Command bind\n";
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

      cout << "Chain bind\n";
      Condiment condiments;
      condiments.description = bind(&accu<string>, &Milk::description, condiments.description);
      condiments.description = bind(&accu<string>, &Sugar::description, condiments.description);
      condiments.description = bind(&accu<string>, &Sugar::description, condiments.description);

      condiments.price = bind(&accu<float>, &Milk::price, condiments.price);
      condiments.price = bind(&accu<float>, &Sugar::price, condiments.price);
      condiments.price = bind(&accu<float>, &Sugar::price, condiments.price);

      cout << "Condiments: " << condiments.description() << '\n';
      cout << "Price: " << condiments.price() << '\n';

      cout << "Factory bind\n";
      BeverageFactory factory;
      factory.create("Coffee")->prepareReceipe();
      factory.create("Tea")->prepareReceipe();
    }

    //#if defined(__GNUC__) || defined(__clang__)
    {
      using namespace cpp11;

      cout << "Strategy lambda\n";
      CaffeineBeverage coffee([]{ return Receipes::amountWaterMl(150); }, []{ Receipes::brewCoffee(); });
      CaffeineBeverage tea([]{ return Receipes::amountWaterMl(200); }, []{ Receipes::brewTea(); });

      using Beverages = vector<CaffeineBeverage*>;
      Beverages beverages;

      beverages.push_back(&coffee);
      beverages.push_back(&tea);

      for(auto beverage : beverages){ beverage->prepareReceipe(); }

      cout << "Command lambda\n";
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

      cout << "Chain lambda\n";
      function<string()> condimentDescription;
      condimentDescription = [=] { return accu(&Milk::description, condimentDescription); };
      condimentDescription = [=] { return accu(&Sugar::description, condimentDescription); };
      condimentDescription = [=] { return accu(&Sugar::description, condimentDescription); };

      function<float()> condimentPrice;
      condimentPrice = [=] { return accu(&Milk::price, condimentPrice); };
      condimentPrice = [=] { return accu(&Sugar::price, condimentPrice); };
      condimentPrice = [=] { return accu(&Sugar::price, condimentPrice); };

      cout << "Condiments: " << condimentDescription() << '\n';
      cout << "Price: " << condimentPrice() << '\n';
    }
  }

  return 0;
}
