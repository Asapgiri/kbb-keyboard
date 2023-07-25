#include <stdio.h>
#include <stdint.h>
#include <windows.h>
#include "KBBSerial.h"


int main(){
   char Port[] = "COM36";
   char* buff = new char[1000];

   KBBSerial Serial(Port);
}