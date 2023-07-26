#include "KeyboardMapInterface.h"
#include <Arduino.h>

KeyboardMapInterface::KeyboardMapInterface() : MapInterface(SLAVE){
   memset(this->MacroTable, 0, sizeof(MacroTable));
}

KeyboardMapInterface::~KeyboardMapInterface(){

}

char KeyboardMapInterface::Sync(void* map, int size){
   
}
