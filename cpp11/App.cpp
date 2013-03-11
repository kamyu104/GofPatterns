// /Users/Tobias/Downloads/checker-270/bin/clang++ -std=c++0x -stdlib=libc++ -I./ -I../ -I/Developer/Library/boost_1_51_0 -o app_cpp11 app.cpp
// #include <CaffeineBeverage.h>
// #include <Recipes.h>
// #include <CoffeeMachine.h>
// #include <View.h>
// #include <MilkFoam.h>
// #include <accu.h>
// #include <Milk.h>
// #include <Sugar.h>
// #include <BeverageFactory.h>
// #include <Condiment.h>
// #include <CondimentFactory.h>

// #include <functional>
// #include <vector>
// #include <memory>

// Boost.MSM tutorial
// back-end
#include <boost/msm/back/state_machine.hpp>
//front-end
#include <boost/msm/front/state_machine_def.hpp>
// functors
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>
// for And_ operator
#include <boost/msm/front/euml/operator.hpp>

using namespace std;
namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace msm::front;
// for And_ operator
using namespace msm::front::euml;

struct evt_beverage
{
  //  std::function<void()> prepare;
};

struct quit
{};

struct evt_condiment
{
//  Condiment _;
};

struct sm_coffeeMachine_ : public msm::front::state_machine_def<sm_coffeeMachine_>
{
  template <class Event,class FSM>
  void on_entry(Event const& ,FSM&) 
  {
    std::cout << "entering: sm_coffeeMachine_" << std::endl;
  }

  template <class Event,class FSM>
  void on_exit(Event const&,FSM& ) 
  {
    std::cout << "leaving: sm_coffeeMachine_" << std::endl;
  }

  struct state_beverage : public msm::front::state<>
  {
    template <class Event,class FSM>
    void on_entry(Event const&,FSM& ) {std::cout << "entering: state_beverage" << std::endl;}
    template <class Event,class FSM>
    void on_exit(Event const&,FSM& ) {std::cout << "leaving: state_beverage" << std::endl;}
  };

  struct state_condiment : public msm::front::state<>
  {
    template <class Event,class FSM>
    void on_entry(Event const&,FSM& ) {std::cout << "entering: state_condiment" << std::endl;}
    template <class Event,class FSM>
    void on_exit(Event const&,FSM& ) {std::cout << "leaving: state_condiment" << std::endl;}
  };

  typedef state_beverage initial_state;

  struct action_add_beverage
  {
    template <class EVT,class FSM,class SourceState,class TargetState>
    void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
    {
      cout << "action_add_beverage" << endl;
    }
  };

  struct action_add_condiment
  {
    template <class EVT,class FSM,class SourceState,class TargetState>
    void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
    {
      cout << "action_add_condiment" << endl;
    }
  };

  struct transition_table : mpl::vector
    <
      //         Start            Event             Next             Action               Guard
      //       +----------------+-----------------+----------------+---------------------+----------------------+
      Row      < state_beverage , evt_beverage    , state_condiment, action_add_beverage , none                 >,
      Row      < state_condiment, evt_condiment   , none           , action_add_condiment, none                 >
    >
  {};
};

typedef msm::back::state_machine<sm_coffeeMachine_> coffeeMachine;

int main()
{
  coffeeMachine c;
  c.start();

  c.process_event(evt_beverage());
c.process_event(evt_condiment());

  c.stop();
}
// Boost.Signals2 tutorial
// #include <boost/signals2.hpp>
// #include <boost/shared_ptr.hpp>
//   using namespace boost::signals2;

//   void hello() 
//   { 
//     std::cout << "Hello "; 
//   } 
  
//   struct World
//   {
//     void operator()()
//     {
//       std::cout << "World";
//     }
//   };

//   struct CoutChar
//   {
//     CoutChar(char c)
//       : letter(c)
//     {}

//     void print()
//     {
//       std::cout << letter;
//     }

//     char letter;
//   };

//   int main() 
//   { 
//     World world;
//     CoutChar c('!');
//     signal<void ()> s;
 
//     s.connect(&hello);
//     s.connect(world);
//     s.connect(std::bind(&CoutChar::print, c)); 
//     s(); 

// /*
//   Hello World!
// */

//     s.disconnect_all_slots();
//     s.connect(1, world);
//     s.connect(0, &hello);
//     s.connect(2, std::bind(&CoutChar::print, c)); 
//     s(); 

// /*
//   Hello World!
// */

//     s.disconnect_all_slots();
//     s.connect(1, world);
//     s.connect(0, &hello);
//     {
//       std::shared_ptr<CoutChar> c(new CoutChar('!'));
//       s.connect(2,
// 		signal<void()>::slot_type(
// 					  &CoutChar::print,
// 					  c.get()).track_foreign(c));
//       std::cout << s.num_slots();
//     }
//     s(); 
//     std::cout << s.num_slots();

//     /*
//   3
//   Hello World
//   2
//      */
//   }
/*
int main(int argc, char* argv[])
{
  using namespace std;
  using namespace cpp11;*/
  /* { // bind
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
  }*/
  /*  { // lambda
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
      }*/
  /*
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
  view.askForCondiments(dummy);*/
//}

