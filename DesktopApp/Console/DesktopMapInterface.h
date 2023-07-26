#ifndef _DESKTOP_MAP_INTERFACE_
#define _DESKTOP_MAP_INTERFACE_

#include "MapInterface.h"

class DesktopMapInterface : public virtual MapInterface{
public:
   DesktopMapInterface();
   ~DesktopMapInterface();
   char Sync(void* map, int size);
};

#endif