#include "KeyboardMacroInterface.h"
#include <Arduino.h>

KeyboardMacroInterface::KeyboardMacroInterface() : MacroInterface(SLAVE){
   memset(this->MacroTable, 0, sizeof(MacroTable));
}

KeyboardMacroInterface::~KeyboardMacroInterface(){

}

char KeyboardMacroInterface::Handshake(char outgoing){
   if(Serial.available()){
      if (0 == Sync())
      {
         return Handshake(outgoing);
      }
      else{
         return 1;
      }
   }
   else{
      Serial.write(outgoing);
      return Serial.read() != outgoing;
   }
   return 0;
}

char KeyboardMacroInterface::Sync(){
   
   if (Serial.available())
   {
      char value = Serial.read();
      if (value == SYNC_MESSAGE)
      {
         Serial.write(SYNC_MESSAGE);
         char incomingMacroSize;
         if(Serial.readBytes(&incomingMacroSize, 1))
         {
            if(Serial.readBytes((unsigned char*)MacroTable, incomingMacroSize))
            {
               return 0;
            }
         }
      }
   }
   return 1;
}
