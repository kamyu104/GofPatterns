#ifndef cpp11_View_h
#define cpp11_View_h

#include <utils/NoCopyNoMove.h>
#include <iostream>

namespace cpp11
{
  class View
  {
  public:
    View()
      {}

    void coffeeMachineFinished()
    {
      std::cout << "Orders are ready to be served\n";
    }

    bool askForBeverage(std::string& beverage)
    {
      std::cout << "Coffeemachine now ready for taking orders or q for quit!" << std::endl;
      std::getline(std::cin, beverage);
      return (beverage != "q");
    }

    bool askForCondiments(std::string& condiment)
    {
      std::cout << "Choose condiments or q for next beverage order:" << std::endl;
      std::getline(std::cin, condiment);
      return (condiment != "q");
    }

  private:
    NO_COPY_NO_MOVE(View);
  };
}

#endif

