#include "KBBSerial.h"
#include "DesktopMapInterface.h"

#define NUMBER_OF_ARROWS  4
#define NUMBER_OF_SEGS    8
#define KEYS_IN_SEGS      8

struct char_holder {
  char def;
  char fn;
  void (*fn_press)(void);
  void (*fn_release)(void);
};

KBBSerial* Serial;
DesktopMapInterface* Interface;

static struct char_holder Keyboard_Layout[NUMBER_OF_SEGS][KEYS_IN_SEGS];
static struct char_holder Desktop_Layout[NUMBER_OF_SEGS][KEYS_IN_SEGS];

static struct char_holder Keyboard_Layout_Arrows[NUMBER_OF_ARROWS];
static struct char_holder Desktop_Layout_Arrows[NUMBER_OF_ARROWS];

void SyncMaps(){
   char a = WATERMARK;
   Serial->Write(&a, 1);
   Interface->SyncKeyMap(Keyboard_Layout, Keyboard_Layout,sizeof(Keyboard_Layout));
   Interface->SyncArrowMap(Keyboard_Layout_Arrows, Keyboard_Layout_Arrows,sizeof(Keyboard_Layout_Arrows));
}

int main(){
   char Port[] = "COM41";
   Serial = new KBBSerial(Port);

   Interface = new DesktopMapInterface(Serial);

   SyncMaps();
   for(int i = 0; i < NUMBER_OF_SEGS; i++){
      printf("\r\n");
      for(int j = 0; j < KEYS_IN_SEGS; j++){
         printf("%d", Keyboard_Layout[i][j]);
      }
   }
}