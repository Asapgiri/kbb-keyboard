#define MASTER 0
#define SLAVE 1

#define SYNC_MESSAGE 0xF0

#ifndef _MAP_INTERFACE_
#define _MAP_INTERFACE_

struct Macro{
   char id;
   char keys[10];
   char keyboardresult;
   char desktopresutl;
};


class MapInterface{
private:
char mode;
public:
   MapInterface(char mode);
   ~MapInterface();
   virtual char Sync(void* map, size_t size) = 0;
};

#endif