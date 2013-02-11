#ifndef cpp11_CoffeeMachine_h
#define cpp11_CoffeeMachine_h

#include <utils/NoCopyNoMove.h>
#include <boost/signals2.hpp>
#include <vector>
#include <functional>

namespace cpp11
{
  class CoffeeMachine
  {
  private:
    typedef std::vector<std::function<void()>> CommandQ;

  public:
  CoffeeMachine()
    : m_commands()
      , m_sigFinished()
      {}

    void request(CommandQ::value_type c)
    {
      m_commands.push_back(c);
    }

    void start()
    {
      for(auto const& cmd : m_commands){ cmd(); }
      /*	for_each(
		begin(m_commands), end(m_commands),
		[](CommandQ::value_type c){ c(); });*/
      m_commands.clear();
      m_sigFinished();
    }

    void getNotifiedOnFinished(std::function<void()> callback)
    {
      m_sigFinished.connect(callback);
    }

  private:
    CommandQ m_commands;
    boost::signals2::signal<void()> m_sigFinished;

    NO_COPY_NO_MOVE(CoffeeMachine);
  };
}

#endif
