#include "KBBSerial.h"

KBBSerial::KBBSerial(char* Port, unsigned int BufferSize, DWORD baudrate, BYTE byteSize, BYTE stopBits, BYTE parity){
   
   char file[64] = "\\\\.\\";
   strcat(file, Port);
   serialHandle = CreateFile(file, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
   
   DCB serialParams = { 0 };
   serialParams.DCBlength = sizeof(serialParams);

   GetCommState(serialHandle, &serialParams);
   serialParams.BaudRate = baudrate;
   serialParams.ByteSize = byteSize;
   serialParams.StopBits = stopBits;
   serialParams.Parity = parity;
   SetCommState(serialHandle, &serialParams);
   
   
   ReadBuffer = new char[BufferSize];
   WriteBuffer = new char[BufferSize];
   SetTimeouts();
}

KBBSerial::~KBBSerial(){
   CloseHandle(serialHandle);
   delete[] WriteBuffer;
   delete[] ReadBuffer;
}

void KBBSerial::SetTimeouts(DWORD ReadIntervalTimeout, DWORD ReadTotalTimeoutConstant, DWORD ReadTotalTimeoutMultiplier, DWORD WriteTotalTimeoutConstant, DWORD WriteTotalTimeoutMultiplier){
   COMMTIMEOUTS timeout = { 0 };
   timeout.ReadIntervalTimeout = ReadIntervalTimeout;
   timeout.ReadTotalTimeoutConstant = ReadTotalTimeoutConstant;
   timeout.ReadTotalTimeoutMultiplier = ReadTotalTimeoutMultiplier;
   timeout.WriteTotalTimeoutConstant = WriteTotalTimeoutConstant;
   timeout.WriteTotalTimeoutMultiplier = WriteTotalTimeoutMultiplier;

   SetCommTimeouts(serialHandle, &timeout);
}


unsigned char KBBSerial::Write(char* data, size_t len){
   memcpy(WriteBuffer, data, len);
   return WriteFile(serialHandle, WriteBuffer, len, 0, NULL);
}

const char* KBBSerial::Read(size_t len){
   ReadFile(serialHandle, ReadBuffer, len , 0, NULL);
   return ReadBuffer;
}
