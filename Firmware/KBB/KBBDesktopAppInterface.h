#include "eXtensionInterface.h"

#ifndef _KBBDesktopAppInterface_H_
#define _KBBDesktopAppInterface_H_

class KBBKeyboardInterface : public ExtensionInterface{
public:
  KBBKeyboardInterface();
  ~KBBKeyboardInterface();
  int SendCommandToApp(char* data, size_t len);
  const char* RecvCommandFromApp();
  int Sync();
};

#endif
