#ifndef utils_NoCopy_h
#define utils_NoCopy_h

#define NO_COPY(className)			\
  private: className(className const&);		\
private: className& operator=(className const&)

#endif
