#ifndef TeaReceipe_h
#define TeaReceipe_h

#include <utils/NoCopy.h>
#include <iostream>

namespace classic
{
    class TeaReceipe : public Receipe
    {
    public:
      TeaReceipe(int minutes)
      : Receipe()
      , m_minutes(minutes)
      {}

      virtual void brew()
      {
	std::cout << m_minutes << "min steeping Tea through filter\n";
      }

      virtual void addCondiments()
      {
	std::cout << "Adding Lemon\n";
      }

    private:
      int m_minutes;

      NO_COPY(TeaReceipe);
    };
}

#endif
