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

// // Boost.MSM tutorial
// // back-end
// #include <boost/msm/back/state_machine.hpp>
// //front-end
// #include <boost/msm/front/state_machine_def.hpp>
// // functors
// #include <boost/msm/front/functor_row.hpp>
// #include <boost/msm/front/euml/common.hpp>
// // for And_ operator
// #include <boost/msm/front/euml/operator.hpp>

// using namespace std;
// namespace msm = boost::msm;
// namespace mpl = boost::mpl;
// using namespace msm::front;
// // for And_ operator
// using namespace msm::front::euml;

// namespace event
// {
//   struct ping
//   {};

//   struct pong
//   {};
// }

// struct sm_ : public msm::front::state_machine_def<sm_>
// {
//   template <class Event,class FSM>
//   void on_entry(Event const& ,FSM&) 
//   {
//     std::cout << "entering: sm_\n";
//   }

//   template <class Event,class FSM>
//   void on_exit(Event const&,FSM& ) 
//   {
//     std::cout << "leaving: sm_\n";
//   }

//   struct state_1 : public msm::front::state<>
//   {
//     template <class Event,class FSM>
//     void on_entry(Event const&,FSM& ) {std::cout << "entering: state_1\n"; }
//     template <class Event,class FSM>
//     void on_exit(Event const&,FSM& ) {std::cout << "leaving: state_1\n"; }
//   };

//   struct state_2 : public msm::front::state<>
//   {
//     template <class Event,class FSM>
//     void on_entry(Event const&,FSM& ) {std::cout << "entering: state_2\n"; }
//     template <class Event,class FSM>
//     void on_exit(Event const&,FSM& ) {std::cout << "leaving: state_2\n"; }
//   };

//   typedef state_1 initial_state;

//   struct action_ping_received
//   {
//     template <class EVT,class FSM,class SourceState,class TargetState>
//     void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
//     {
//       std::cout << "action_ping_received\n";
//     }
//   };

//   struct action_pong_received
//   {
//     template <class EVT,class FSM,class SourceState,class TargetState>
//     void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
//     {
//       std::cout << "action_pong_received\n";
//     }
//   };

//   struct transition_table : mpl::vector
//     <
//       //         Start      Event             Next             Action                 Guard
//       //       +----------+-----------------+----------------+----------------------+--------+
//       Row      < state_1  , event::ping     , state_2        , action_ping_received , none   >,
//       Row      < state_2  , event::pong     , state_1        , action_pong_received , none   >
//     >
//   {};

//   template <class FSM,class Event>
//   void no_transition(Event const& e, FSM&,int state)
//   {
//     std::cout << "no transition from state " << state
//               << " on event " << typeid(e).name() << '\n';
//   }
// };

// typedef msm::back::state_machine<sm_> sm;

// int main()
// {
//   sm s;
//   s.start();

//   s.process_event(event::ping());
//   s.process_event(event::pong());

//   s.process_event(event::ping());
//   s.process_event(event::pong());

//   s.process_event(event::pong());

//   s.stop();
// }
// // Boost.Signals2 tutorial
// // #include <boost/signals2.hpp>
// // #include <boost/shared_ptr.hpp>
// //   using namespace boost::signals2;

// //   void hello() 
// //   { 
// //     std::cout << "Hello "; 
// //   } 
  
// //   struct World
// //   {
// //     void operator()()
// //     {
// //       std::cout << "World";
// //     }
// //   };

// //   struct CoutChar
// //   {
// //     CoutChar(char c)
// //       : letter(c)
// //     {}

// //     void print()
// //     {
// //       std::cout << letter;
// //     }

// //     char letter;
// //   };

// //   int main() 
// //   { 
// //     World world;
// //     CoutChar c('!');
// //     signal<void ()> s;
 
// //     s.connect(&hello);
// //     s.connect(world);
// //     s.connect(std::bind(&CoutChar::print, c)); 
// //     s(); 

// // /*
// //   Hello World!
// // */

// //     s.disconnect_all_slots();
// //     s.connect(1, world);
// //     s.connect(0, &hello);
// //     s.connect(2, std::bind(&CoutChar::print, c)); 
// //     s(); 

// // /*
// //   Hello World!
// // */

// //     s.disconnect_all_slots();
// //     s.connect(1, world);
// //     s.connect(0, &hello);
// //     {
// //       std::shared_ptr<CoutChar> c(new CoutChar('!'));
// //       s.connect(2,
// // 		signal<void()>::slot_type(
// // 					  &CoutChar::print,
// // 					  c.get()).track_foreign(c));
// //       std::cout << s.num_slots();
// //     }
// //     s(); 
// //     std::cout << s.num_slots();

// //     /*
// //   3
// //   Hello World
// //   2
// //      */
// //   }

int main(int argc, char* argv[])
{
  using namespace std;
  using namespace cpp11;
  /** [using bind] */
  // { // bind
  //   using Beverages = std::vector<std::unique_ptr<CaffeineBeverage>>;
  //   Beverages beverages;
  //   CoffeeMachine coffeeMachine;
  //   View view;
  //   BeverageFactory beverageFactory;

  //   coffeeMachine.getNotifiedOnFinished(bind(&View::coffeeMachineFinished, &view));
  //   do
  //     {
  // 	std::string inBeverage;
  // 	if(!view.askForBeverage(inBeverage)) break;
  // 	beverages.emplace_back(beverageFactory.create(inBeverage));
  // 	Condiment condiments;
  // 	do
  // 	  {
  // 	    CondimentFactory condimentFactory;
  // 	    std::string inCondiment;
  // 	    if(!view.askForCondiments(inCondiment)) break;
  // 	    Condiment condiment = condimentFactory.create(inCondiment);
  // 	    condiments.description = bind(&accu<string>, condiment.description, condiments.description);
  // 	    condiments.price = bind(&accu<float>, condiment.price, condiments.price);
  // 	  } while(true);
  // 	beverages.back()->condiments(condiments);
  //     } while(true);
  //   if(!beverages.empty())
  //     {
  // 	for(auto& beverage : beverages)
  // 	  {
  // 	    coffeeMachine.request(bind(&CaffeineBeverage::prepare, &(*beverage)));
  // 	  }
  // 	coffeeMachine.start();
  // 	for(auto& beverage : beverages)
  // 	  {
  // 	    beverage->description();
  // 	    beverage->price();
  // 	  }
  //     }
  // }
  /** [using bind] */
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

  // using Beverages = std::vector<std::unique_ptr<CaffeineBeverage>>;
  // Beverages beverages;
  // CoffeeMachine coffeeMachine;
  // View view;
  // BeverageFactory beverageFactory;

  // auto start = std::chrono::high_resolution_clock::now();

  // for(int i = 0; i < 10; ++i)
  //   {
  //     beverages.emplace_back(beverageFactory.create("Coffee"));
  //     Condiment condiments;
  //     for(int i = 0; i < 10; ++i)
  // 	{
  // 	  CondimentFactory condimentFactory;
  // 	  Condiment condiment = condimentFactory.create("Milk");
  // 	  condiments.description = [=]{ return accu(condiment.description, condiments.description); };
  // 	  condiments.price = [=]{ return accu(condiment.price, condiments.price); };
  // 	}
  //     beverages.back()->condiments(condiments);
  //   }
  // if(!beverages.empty())
  //   {
  //     for(auto& beverage : beverages)
  // 	{
  // 	  coffeeMachine.request([&]{ beverage->prepare(); });
  // 	}
  //     coffeeMachine.start();
  //     for(auto& beverage : beverages)
  // 	{
  // 	  beverage->description();
  // 	  beverage->price();
  // 	}
  //   }

  // auto end = std::chrono::high_resolution_clock::now();

  // auto elapsed = end - start;
  // std::cout << elapsed.count() << '\n';
  // std::string dummy;
  // view.askForCondiments(dummy);
}
