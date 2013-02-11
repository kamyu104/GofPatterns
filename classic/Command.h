#ifndef classic_Command_h
#define classic_Command_h

namespace classic
{
    class Command
    {
    public:
      virtual ~Command() {}
      virtual void execute() = 0;
    };
}

#endif
