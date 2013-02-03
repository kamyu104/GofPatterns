#ifndef classic_Command_h
#define classic_Command_h

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
