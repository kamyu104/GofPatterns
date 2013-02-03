#ifndef Command_h
#define Command_h

#include <utils/NoCopy.h>

namespace classic
{
    class Command
    {
    public:
      virtual void execute() = 0;
    };
}

#endif
