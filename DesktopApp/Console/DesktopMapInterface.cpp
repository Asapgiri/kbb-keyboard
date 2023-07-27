#include "DesktopMapInterface.h"

DesktopMapInterface::DesktopMapInterface(): MapInterface(MASTER)
{
   this->Serial = nullptr;
}
DesktopMapInterface::DesktopMapInterface(KBBSerial* serial): MapInterface(MASTER)
{
   this->Serial = serial;
}

DesktopMapInterface::~DesktopMapInterface()
{

}

char DesktopMapInterface::SyncKeyMap(void* Old_KeyMap, void* new_KeyMap, int size)
{
   const char* buff = Serial->Read(1);
   if(*buff == KEY_MAP_WATERMARK){
      Serial->Read(1);
      Serial->Read(*buff);
      memcpy(Old_KeyMap, buff, size);

      Serial->Write((char*) new_KeyMap,(size_t) size);
   }
}

char DesktopMapInterface::SyncArrowMap(void* Old_KeyMap, void* new_KeyMap, int size)
{
   const char* buff = Serial->Read(1);
   if(*buff == ARROW_MAP_WATERMARK){
      Serial->Read(1);
      Serial->Read(*buff);
      memcpy(Old_KeyMap, buff, size);

      Serial->Write((char*) new_KeyMap, (size_t) size);
   }
}