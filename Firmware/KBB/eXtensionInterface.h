#include <Arduino.h>
#ifndef _ExtensionInterface_H_
#define _ExtensionInterface_H_
class ExtensionInterface
{
public:
  ExtensionInterface();
  ~ExtensionInterface();
  virtual int SendCommandToApp(char* data, size_t len)= 0;
  virtual const char* RecvCommandFromApp() = 0;
};
#endif
