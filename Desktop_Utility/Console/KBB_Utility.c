#include <stdio.h>
#include <stdint.h>
#include <windows.h>

int main(){
   HANDLE serialHandle = CreateFile("\\\\.\\COM39", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

   // Do some basic settings
   DCB serialParams = { 0 };
   serialParams.DCBlength = sizeof(serialParams);

   GetCommState(serialHandle, &serialParams);
   serialParams.BaudRate = 9600;
   serialParams.ByteSize = 8;
   serialParams.StopBits = TWOSTOPBITS;
   serialParams.Parity = NOPARITY;
   SetCommState(serialHandle, &serialParams);

   // Set timeouts
   COMMTIMEOUTS timeout = { 0 };
   timeout.ReadIntervalTimeout = 50;
   timeout.ReadTotalTimeoutConstant = 50;
   timeout.ReadTotalTimeoutMultiplier = 50;
   timeout.WriteTotalTimeoutConstant = 50;
   timeout.WriteTotalTimeoutMultiplier = 10;

   SetCommTimeouts(serialHandle, &timeout);

   

   CloseHandle(serialHandle);
   return 0;
}