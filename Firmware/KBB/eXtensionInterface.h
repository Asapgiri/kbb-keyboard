#include <Arduino.h>
#ifndef _ExtensionInterface_H_
#define _ExtensionInterface_H_

#define HOST 0
#define SLAVE 1


/*struct Command{
  int id;
  int char Keys[10];
  int char SlaveMacro[10];
  int char HostMacro[10];
};*/

class ExtensionInterface
{
public:
  ExtensionInterface();
  ~ExtensionInterface();
  virtual int SendMessage(char* data, size_t len)= 0;
  virtual const char* RecvMessage(size_t len) = 0;
  virtual int Sync() = 0;
};
#endif
