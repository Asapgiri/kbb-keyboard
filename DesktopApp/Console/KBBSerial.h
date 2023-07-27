#ifndef _KBB_SERIAL_H
#define _KBB_SERIAL_H

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <windows.h>

class KBBSerial{
public:
   KBBSerial(char* Port, unsigned int BufferSize = 1024, DWORD baudrate = 9600, BYTE byteSize = 8, BYTE stopBits = TWOSTOPBITS, BYTE parity = NOPARITY);
   ~KBBSerial();
   void SetTimeouts(DWORD ReadIntervalTimeout = 50, DWORD ReadTotalTimeoutConstant = 50, DWORD ReadTotalTimeoutMultiplier = 50, DWORD WriteTotalTimeoutConstant = 50, DWORD WriteTotalTimeoutMultiplier = 10);
   unsigned char Write(char* data, size_t len);
   const char* Read(size_t len);
private:
   HANDLE serialHandle;
   char* ReadBuffer;
   char* WriteBuffer;
};

#endif