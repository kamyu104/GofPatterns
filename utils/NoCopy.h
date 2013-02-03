#define NO_COPY(className)			\
  private: className(className const&);		\
private: className& operator=(className const&)
