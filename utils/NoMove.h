#ifndef utils_NoMove_h
#define utils_NoMove_h

#define NO_MOVE(className)			\
  private: className(className&&);		\
private: className&& operator=(className&&)

#endif
