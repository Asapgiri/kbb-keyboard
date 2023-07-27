#include "KeyboardMapInterface.h"
#include <Arduino.h>


KeyboardMapInterface::KeyboardMapInterface() : MapInterface(SLAVE){
   
}


KeyboardMapInterface::~KeyboardMapInterface(){

}


char KeyboardMapInterface::SyncKeyMap(void* Old_KeyMap, void* new_KeyMap, int size)
{
   Serial.write(KEY_MAP_WATERMARK);
   Serial.write(size);
   Serial.write((const unsigned char*) Old_KeyMap, (char) size);

   Serial.readBytes((char*) new_KeyMap,(size_t) size);
}


char KeyboardMapInterface::SyncArrowMap(void* Old_KeyMap, void* new_KeyMap, int size)
{
   Serial.print(ARROW_MAP_WATERMARK);
   Serial.print(size);
   Serial.write((const unsigned char*) Old_KeyMap, (char) size);

   Serial.readBytes((char*) new_KeyMap,(size_t) size);
}
