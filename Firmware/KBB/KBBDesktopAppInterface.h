#include "eXtensionInterface.h"

#ifndef _KBBDesktopAppInterface_H_
#define _KBBDesktopAppInterface_H_

class KBBDesktopAppInterface : public ExtensionInterface{
public:
  KBBDesktopAppInterface();
  ~KBBDesktopAppInterface();
  int SendCommandToApp(char* data, size_t len);
  const char* RecvCommandFromApp();
}

#endif
