#include "MacroInterface.h"

#ifndef _KEYBOARD_MACRO_INTERFACE_
#define _KEYBOARD_MACRO_INTERFACE_

class KeyboardMacroInterface : public virtual MacroInterface {
private:
   struct Macro MacroTable[100];
public:
   KeyboardMacroInterface();
   ~KeyboardMacroInterface();
   char Sync();
   char Handshake(char outgoing);
};

#endif