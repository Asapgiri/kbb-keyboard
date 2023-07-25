#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include "lib\simple_serial_port\simple-serial-port\simple-serial-port\SimpleSerial.h"

int main(){
   char com_port[] = "\\\\.\\COM8";
   DWORD COM_BAUD_RATE = CBR_9600;
   SimpleSerial Serial(com_port, COM_BAUD_RATE);

   /*if(connected_) {
      //do whatever
   }*/
   return 0;
}