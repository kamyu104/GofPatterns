#ifndef utils_NoCopyNoMove_h
#define utils_NoCopyNoMove_h

#include <utils/NoCopy.h>
#include <utils/NoMove.h>

#define NO_COPY_NO_MOVE(className)		\
  NO_COPY(className);				\
  NO_MOVE(className)

#endif
