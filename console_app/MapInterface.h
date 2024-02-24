#ifndef _MAP_INTERFACE_
#define _MAP_INTERFACE_

#define SYNC_MESSAGE 0xF0
#define MASTER 0
#define SLAVE 1

class MapInterface{
private:
char mode;
public:
   MapInterface(char mode);
   ~MapInterface();
   virtual char Sync(void* map, int size) = 0;
};

#endif