#ifndef _MAP_INTERFACE_
#define _MAP_INTERFACE_

#define SYNC_MESSAGE 0xF0
#define MASTER 0
#define SLAVE 1
#define WATERMARK 0xAA
#define KEY_MAP_WATERMARK 0xAB
#define ARROW_MAP_WATERMARK 0xAC

class MapInterface{
private:
char mode;
public:
   MapInterface(char mode);
   ~MapInterface();
   virtual char SyncKeyMap(void* Old_KeyMap, void* new_KeyMap, int size) = 0;
   virtual char SyncArrowMap(void* Old_KeyMap, void* new_KeyMap, int size) = 0;
};

#endif