// /Users/Tobias/Downloads/checker-270/bin/clang++ --std=c++0x -o patterns_clang patterns.cpp

// /Users/Tobias/Downloads/checker-270/scan-build -o ./scan -v -v -v /Users/Tobias/Downloads/checker-270/bin/clang++ -o patterns_clang patterns.cpp

// g++ --std=C++0x -o patterns_gcc patterns.cpp

// D:\Projects\C++\gcc_4.7_20110903\bin\g++.exe --std=c++0x patterns.cpp -o patterns_gcc
 
// D:\Projects\C++\llvm\build\bin\Debug\clang-interpreter.exe -v -o patterns_clang patterns.cpp
 
// "C:\Program Files\Microsoft Visual Studio 10.0\VC\bin\vcvars32.bat" & "C:\Program Files\Microsoft Visual Studio 10.0\VC\bin\cl.exe" /EHsc /nologo /W4 /NTd patterns.cpp
 
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
 
#define NO_COPY(className) \
    private: className(className const&); \
    private: className& operator=(className const&)
 
#define NO_MOVE(className) \
    private: className(className&&); \
    private: className&& operator=(className&&)
 
#define NO_COPY_NO_MOVE(className) \
    NO_COPY(className); \
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
 
            void add()
     {
                if(m_next) m_next->add();
                this->onAdd();
     }
            
        private:
            virtual void onAdd() = 0;
            
            Condiment* m_next;
        };
 
        class ReceipeWithCondiments : public Receipe
        {
        public:
            virtual void addCondiments()
            {
                m_condiment->add();
     }
 
        private:
            Condiment* m_condiment;
 
            NO_COPY(ReceipeWithCondiments);
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
            virtual void onAdd()
            {
                cout << "-Milk-";
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
            virtual void onAdd()
            {
                cout << "-Sugar-";
     }
            
            NO_COPY(Sugar);
        };
        
        class Command
        {
        public:
            virtual void execute() = 0;
        };
 
        class CoffeeMachine
        {
        private:
            typedef vector<Command*> CommandQ;
 
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
 
// namespace cpp11
// {
 
//     namespace beverages
//     {
 
//         struct Receipe
//         {
//         public:
//             function<void()> brew;
//             function<void()> addCondiments;
//         };
    
//         class CaffeineBeverage
//         {
//         public:
//             CaffeineBeverage(Receipe receipe)
//             : m_brew(receipe.brew)
//             , m_addCondiments(receipe.addCondiments)
//             {}
 
//             CaffeineBeverage(function<void()> brew, function<void()> addCondiments)
//             : m_brew(brew)
//             , m_addCondiments(addCondiments)
//             {}
 
//             void prepareReceipe()
//             {
//                 boilWater();
//                 m_brew();
//                 pourInCup();
//                 m_addCondiments();
//             }
 
//         private:
//             void boilWater()
//             {
//                 cout << "boil water\n";
//             }
 
//             void pourInCup()
//             {
//                 cout << "pour in cup\n";
//             }
 
//             function<void()> m_brew;
//             function<void()> m_addCondiments;
 
//             NO_COPY_NO_MOVE(CaffeineBeverage);
//         };
 
//         class Receipes
//         {
//         public:
//             static void brewCoffee(int minutes)
//             {
//                 cout << minutes << "min for dripping Coffee through filter\n";
//             }
 
//             static void brewTea(int minutes)
//             {
//                 cout << minutes << "min for steeping Tea\n";
//             }
 
//             static void addSugarAndMilk()
//             {
//                 cout << "Adding Sugar and Milk\n";
//             }
 
//             static void addLemon()
//             {
//                 cout << "Adding Lemon\n";
//             }
 
//             NO_COPY_NO_MOVE(Receipes);
//         };
 
//         class CoffeeMachine
//         {
//         private:
//             typedef vector<function<void()>> CommandQ;
 
//         public:
//             CoffeeMachine()
//             : m_commands()
//             {}
 
//             void request(CommandQ::value_type c)
//             {
//                 m_commands.push_back(c);
//             }
 
//             void start()
//             {
//                 for_each(
//                     begin(m_commands), end(m_commands),
//                     [](CommandQ::value_type c){ c(); });
//             }
 
//         private:
//             CommandQ m_commands;
 
//             NO_COPY_NO_MOVE(CoffeeMachine);
//         };
 
//         class MilkFoam
//         {
//         public:
//             MilkFoam()
//             {}
 
//             void makeFoam(int mlMilk)
//             {
//                 boilMilk(mlMilk);
//                 pourInCup();
//                 foaming();
//             }
 
//         private:
//             void boilMilk(int mlMilk)
//             {
//                 cout << "boiling " << mlMilk << "ml milk\n";
//             }
 
//             void pourInCup()
//             {
//                 cout << "pour in cup\n";
//             }
 
//             void foaming()
//             {
//                 cout << "foaming\n";
//             }
 
//             NO_COPY_NO_MOVE(MilkFoam);
//         };
 
//     }
 
// }

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
 
            coffeeMachine.request(&makeCoffee);
            coffeeMachine.request(&makeMilkFoam);
 
            coffeeMachine.start();
 
            makeMilkFoam.setMlMilk(200);
            coffeeMachine.request(&makeMilkFoam);
            makeMilkFoam.setMlMilk(300);
            coffeeMachine.request(&makeMilkFoam);
            coffeeMachine.start();
        }
    }
 
    {
//         using namespace cpp11;
//         {
//             using namespace beverages;
 
//             CaffeineBeverage coffee(bind(&Receipes::brewCoffee, 1), &Receipes::addSugarAndMilk);
//             CaffeineBeverage tea(bind(&Receipes::brewTea, 2), &Receipes::addLemon);
 
//             typedef vector<CaffeineBeverage*> Beverages;
//             Beverages beverages;
            
//             beverages.push_back(&coffee);
//             beverages.push_back(&tea);
 
//             using namespace placeholders;
 
//             for_each(
//                 begin(beverages), end(beverages),
//                 bind(&CaffeineBeverage::prepareReceipe, _1));
 
//             CoffeeMachine coffeeMachine;
 
//             coffeeMachine.request(bind(&CaffeineBeverage::prepareReceipe, &coffee));
//             coffeeMachine.request(bind(&CaffeineBeverage::prepareReceipe, &tea));
 
//             MilkFoam milkFoam;
//             coffeeMachine.request(bind(&MilkFoam::makeFoam, &milkFoam, 100));
 
//             coffeeMachine.start();
 
//             coffeeMachine.request(bind(&MilkFoam::makeFoam, &milkFoam, 200));
//             coffeeMachine.request(bind(&MilkFoam::makeFoam, &milkFoam, 300));
//             coffeeMachine.start();
//         }
 
// #if defined(__GNUC__)
//         using namespace cpp11;
//         {
//             using namespace beverages;
 
//             CaffeineBeverage coffee([]{ Receipes::brewCoffee(1); }, []{ Receipes::addSugarAndMilk(); });
//             CaffeineBeverage tea([]{ Receipes::brewTea(2); }, []{ Receipes::addLemon(); });
 
//             typedef vector<CaffeineBeverage*> Beverages;
//             Beverages beverages;
            
//             beverages.push_back(&coffee);
//             beverages.push_back(&tea);
 
//             using namespace placeholders;
 
//             for(auto beverage : beverages){ beverage->prepareReceipe(); }
 
//             CoffeeMachine coffeeMachine;
 
//             MilkFoam milkFoam;
//             coffeeMachine.request([&]{ milkFoam.makeFoam(100); });
//             coffeeMachine.request([&]{ coffee.prepareReceipe(); });
//             coffeeMachine.request([&]{ tea.prepareReceipe(); });
//             coffeeMachine.start();
 
//             coffeeMachine.request([&]{ milkFoam.makeFoam(200); });
//             coffeeMachine.request([&]{ milkFoam.makeFoam(300); });
//             coffeeMachine.start();
//         }
// #endif
    }
 
    return 0;
}
