
#ifndef _KEYBOARD_MAP_INTERFACE_
#define _KEYBOARD_MAP_INTERFACE_

#include "MapInterface.h"

class KeyboardMapInterface : public virtual MapInterface {
public:
   KeyboardMapInterface();
   ~KeyboardMapInterface();
   char SyncKeyMap(void* Old_KeyMap, void* new_KeyMap, int size);
   char SyncArrowMap(void* Old_KeyMap, void* new_KeyMap, int size);
};

#endif