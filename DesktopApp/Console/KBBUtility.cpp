#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <windows.h>
#include "KBBSerial.h"


int main(){
   char Port[] = "COM5";
   const char* buff;

   KBBSerial Serial(Port);
   while (1)
   {
      buff = Serial.Read(1);
      printf(buff);
      sleep(1);
   }
   
}