#ifndef _KBB_H_
#define _KBB_H_

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

#define PIN_ARROW_UP    22
#define PIN_ARROW_DOWN  21
#define PIN_ARROW_LEFT  23
#define PIN_ARROW_RIGHT 20

#define PIN_LED0          30
#define PIN_LED1          1
#define PIN_LED2          0
#define PIN_LED_CAPSLOCK  PIN_LED0
#define PIN_LED_WINLOCK   PIN_LED1


#define NUMBER_OF_SEGS  8
#define KEYS_IN_SEGS    8

#define KEY_LEFT_WIN    0x5B
#define KEY_LEFT_SLEEP  0x5F
#define KEY_VOLUME_UP   0xAF
#define KEY_VOLUME_DOWN 0xAE
#define KEY_MUSIC_PLAY  0xB3
#define KEY_MUSIC_NEXT  0xB0
#define KEY_MUSIC_PREV  0xB1

#define FUNCTION_KEY    0x1



struct char_holder {
  char def;
  char fn;
  void (*fn_press)(void);
  void (*fn_release)(void);
};

class KBB{
private:
  bool fn_pressed;
  bool ActualKeyMap[NUMBER_OF_SEGS][KEYS_IN_SEGS];
  bool LastKeyMap[NUMBER_OF_SEGS][KEYS_IN_SEGS];
  bool PressKeyMap[NUMBER_OF_SEGS][KEYS_IN_SEGS];
  bool ReleaseKeyMap[NUMBER_OF_SEGS][KEYS_IN_SEGS];

public:
  void ChangeSegment(unsigned char seg);
  void begin();
  void RefreshActualKeyMap(unsigned char seg);
  bool CompareActualAndLastKeys(unsigned char seg);
  void CopyActualToLastSegment(unsigned char seg);
  void SendChangesToHost(unsigned char seg);
  KBB();
  ~KBB();
};


#endif _KBB_H_
