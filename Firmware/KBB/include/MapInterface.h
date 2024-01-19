#define MASTER 0
#define SLAVE 1



#ifndef _MAP_INTERFACE_
#define _MAP_INTERFACE_

#define WATERMARK 0x15

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
   virtual char Sync(void* map, int size) = 0;
};

#endif