
#ifndef _KEYBOARD_MAP_INTERFACE_
#define _KEYBOARD_MAP_INTERFACE_

#include "MapInterface.h"

class KeyboardMapInterface : public virtual MapInterface {
private:
   struct Macro MacroTable[100];
public:
   KeyboardMapInterface();
   ~KeyboardMapInterface();
   char Sync(void* map, int size);
};

#endif