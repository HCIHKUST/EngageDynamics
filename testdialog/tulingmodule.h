#ifndef TULINGMODULE_H
#define TULINGMODULE_H

#include <iostream>

using std::string;

class tulingModule
{
public:
  tulingModule();

  virtual void init();

  string getResponse(string text);
};

#endif // TULINGMODULE_H
