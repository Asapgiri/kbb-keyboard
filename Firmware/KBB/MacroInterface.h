#define MASTER 0
#define SLAVE 1

#define SYNC_MESSAGE 0xF0

#ifndef _MACRO_INTERFACE_
#define _MACRO_INTERFACE_

struct Macro{
   char id;
   char keys[10];
   char keyboardresult;
   char desktopresutl;
};


class MacroInterface{
private:
char mode;
public:
   MacroInterface(char mode);
   ~MacroInterface();
   virtual char Sync() = 0;
   virtual char Handshake(char outgoing) = 0;
};

#endif