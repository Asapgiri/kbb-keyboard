#ifndef _DESKTOP_MAP_INTERFACE_
#define _DESKTOP_MAP_INTERFACE_

#include "MapInterface.h"
#include "KBBSerial.h"

class DesktopMapInterface : public virtual MapInterface{
private:
   KBBSerial* Serial;
public:
DesktopMapInterface();
   DesktopMapInterface(KBBSerial* Serial);
   ~DesktopMapInterface();
   char SyncKeyMap(void* Old_KeyMap, void* new_KeyMap, int size);
   char SyncArrowMap(void* Old_KeyMap, void* new_KeyMap, int size);
};

#endif