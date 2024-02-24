
#ifndef _KBB_H_
#define _KBB_H_

#include "MapInterface.h"
//#include <HID-Project.h>

#define SEGMENT_DELAY_US    50

#define PIN_BOARD_EN  3

#define PIN_ADDR_A0 7
#define PIN_ADDR_A1 19
#define PIN_ADDR_A2 18

#define PIN_SEG0 4
#define PIN_SEG1 12
#define PIN_SEG2 6
#define PIN_SEG3 8
#define PIN_SEG4 9
#define PIN_SEG5 10
#define PIN_SEG6 5
#define PIN_SEG7 13

#define PIN_ARROW_UP    23
#define PIN_ARROW_DOWN  21
#define PIN_ARROW_LEFT  22
#define PIN_ARROW_RIGHT 20

#define PIN_LED0          30
#define PIN_LED1          1
#define PIN_LED2          0
#define PIN_LED_CAPSLOCK  PIN_LED0
#define PIN_LED_WINLOCK   PIN_LED1
#define PIN_LED_FNLOCK    PIN_LED2


#define NUMBER_OF_ARROWS  4
#define NUMBER_OF_SEGS    8
#define KEYS_IN_SEGS      8

#define KEY_LEFT_SLEEP    NULL  //NULL  // 0x5F
#define KEY_VOLUME_UP     NULL  //MEDIA_VOLUME_UP
#define KEY_VOLUME_DOWN   NULL  //MEDIA_VOLUME_DOWN
#define KEY_MUSIC_PLAY    NULL  //MEDIA_PLAY_PAUSE
#define KEY_MUSIC_NEXT    NULL  //MEDIA_NEXT
#define KEY_MUSIC_PREV    NULL  //MEDIA_PREVIOUS

#define FUNCTION_KEY    0x1

#define KEY_BUFFER_TYPE         unsigned int
#define KEY_BUFFER_SIZE         (sizeof(KEY_BUFFER_TYPE) << 3)  //  * 8
#define KEY_BUFFER_ACCEPT_TRUE  (sizeof(KEY_BUFFER_TYPE) >> 1)  //  / 2
#define KEY_BUFFER_SIZE_FILER   (KEY_BUFFER_SIZE - 1)   // 0b00000111 = 0x07, accept from 0 to 7


struct char_holder {
  unsigned char def;
  unsigned char fn;
  void (*fn_press)(void);
  void (*fn_release)(void);
};

struct key_map {
  KEY_BUFFER_TYPE buffer;
  KEY_BUFFER_TYPE buffer_pos;
  bool actual;
  bool last;
  bool press;
  bool release;
};



class KBB{
private:
  MapInterface* mapInterface;
  void setMaps();
  unsigned int segment;
  bool fn_pressed;

  struct key_map KeyMapMain[NUMBER_OF_SEGS][KEYS_IN_SEGS];
  struct key_map KeyMapArrows[NUMBER_OF_ARROWS];

  void HandleSendChange(struct char_holder* key, bool press);
  inline void SendPress(char key);
  inline void SendRelease(char key);
  bool CompareLastKeys(struct key_map* keymap, unsigned int len);
  char SaveToEEPROM();
  char ReadFromEEPROM();
  char EEPROM_init();

public:
  void begin();
  void ChangeSegment(unsigned int seg);

  void RefreshKeyMap();
  bool CompareLastKeys();
  void SendSegment();
  void SaveToPastSegment();

  void SyncKeyMap();

  KBB();
  KBB(MapInterface* mapInterface);
  ~KBB();
};


#endif // _KBB_H_
