#include "KBB.h"
#include <Arduino.h>
#include <Keyboard.h>
#include <EEPROM.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Private fields
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool win_locked = false;
static bool fn_locked = false;

static void key_win_lock(void) {
  win_locked = !win_locked;
  digitalWrite(PIN_LED_WINLOCK, win_locked);
}

static void key_fn_lock(void) {
  fn_locked = !fn_locked;
  digitalWrite(PIN_LED_FNLOCK, fn_locked);
}


static struct char_holder Layout[NUMBER_OF_SEGS][KEYS_IN_SEGS] = {
  {
    { def: KEY_ESC,           fn: '`',                fn_press: NULL,         fn_release: NULL },
    { def: 'w',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: '4',               fn: KEY_F4,             fn_press: NULL,         fn_release: NULL },
    { def: '5',               fn: KEY_F5,             fn_press: NULL,         fn_release: NULL },
    { def: '7',               fn: KEY_F7,             fn_press: NULL,         fn_release: NULL },
    { def: '9',               fn: KEY_F9,             fn_press: NULL,         fn_release: NULL },
    { def: '-',               fn: KEY_F11,            fn_press: NULL,         fn_release: NULL },
    { def: KEY_BACKSPACE,     fn: NULL,               fn_press: NULL,         fn_release: NULL }
  },
  {
    { def: '1',               fn: KEY_F1,             fn_press: NULL,         fn_release: NULL },
    { def: '3',               fn: KEY_F3,             fn_press: NULL,         fn_release: NULL },
    { def: 'r',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: '6',               fn: KEY_F6,             fn_press: NULL,         fn_release: NULL },
    { def: '8',               fn: KEY_F8,             fn_press: NULL,         fn_release: NULL },
    { def: '0',               fn: KEY_F10,            fn_press: NULL,         fn_release: NULL },
    { def: '=',               fn: KEY_F12,            fn_press: NULL,         fn_release: NULL },
    { def: KEY_INSERT,        fn: NULL /* KEY_PRINT_SCREEN */,   fn_press: NULL,         fn_release: NULL }
  },
  {
    { def: 'q',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 's',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'f',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'y',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'i',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'p',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: ']',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: KEY_END,           fn: NULL,               fn_press: NULL,         fn_release: NULL }
  },
  {
    { def: KEY_TAB,           fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: '2',               fn: KEY_F2,             fn_press: NULL,         fn_release: NULL },
    { def: 'e',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 't',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'u',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'o',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: '[',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: '\\',              fn: NULL,               fn_press: NULL,         fn_release: NULL }
  },
  {
    { def: KEY_LEFT_WIN,      fn: NULL,               fn_press: key_win_lock, fn_release: NULL }, // Left WIN
    { def: 'x',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'v',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'h',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'k',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: ';',               fn: KEY_MUSIC_PREV,     fn_press: NULL,         fn_release: NULL },
    { def: KEY_RIGHT_SHIFT,   fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: KEY_DELETE,        fn: NULL,               fn_press: NULL,         fn_release: NULL }
  },
  {
    { def: KEY_CAPS_LOCK,     fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'a',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'd',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'g',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'j',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'l',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: '\'',              fn: KEY_MUSIC_NEXT,     fn_press: NULL,         fn_release: NULL },
    { def: KEY_RETURN,        fn: NULL,               fn_press: NULL,         fn_release: NULL }
  },
  {
    { def: KEY_LEFT_CTRL,     fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: KEY_LEFT_ALT,      fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: ' ',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'n',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: ',',               fn: KEY_VOLUME_DOWN,    fn_press: NULL,         fn_release: NULL },
    { def: KEY_RIGHT_ALT,     fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: FUNCTION_KEY,      fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: KEY_HOME,          fn: KEY_LEFT_SLEEP,     fn_press: NULL,         fn_release: NULL }
  },
  {
    { def: KEY_LEFT_SHIFT,    fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'z',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'c',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'b',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: 'm',               fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: '.',               fn: KEY_VOLUME_UP,      fn_press: NULL,         fn_release: NULL },
    { def: '/',               fn: KEY_MUSIC_PLAY,     fn_press: NULL,         fn_release: NULL },
    { def: NULL,              fn: NULL,               fn_press: NULL,         fn_release: NULL }
  }
};

static struct char_holder Layout_Arrows[NUMBER_OF_ARROWS] = {
    { def: KEY_UP_ARROW,      fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: KEY_DOWN_ARROW,    fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: KEY_LEFT_ARROW,    fn: NULL,               fn_press: NULL,         fn_release: NULL },
    { def: KEY_RIGHT_ARROW,   fn: NULL,               fn_press: key_fn_lock,  fn_release: NULL }
};

static unsigned int pin_map_main[NUMBER_OF_SEGS] = {
  PIN_SEG0,
  PIN_SEG1,
  PIN_SEG2,
  PIN_SEG3,
  PIN_SEG4,
  PIN_SEG5,
  PIN_SEG6,
  PIN_SEG7
};

static unsigned int pin_map_arrows[NUMBER_OF_ARROWS] = {
  PIN_ARROW_UP,
  PIN_ARROW_DOWN,
  PIN_ARROW_LEFT,
  PIN_ARROW_RIGHT
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Public fields
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void KBB::setMaps()
{
  fn_pressed = false;

  memset(KeyMapMain,   false, sizeof(KeyMapMain));
  memset(KeyMapArrows, false, sizeof(KeyMapArrows));
}

KBB::KBB() 
{
  this->mapInterface = nullptr;
  setMaps();
}

KBB::KBB(MapInterface* mapInterface)
{
  this->mapInterface = mapInterface;
  setMaps();
}

KBB::~KBB() 
{
  /*Nothing to do yet*/
}


char KBB::EEPROM_init()
{
  EEPROM.update(0, WATERMARK);
}

char KBB::SaveToEEPROM()
{
  EEPROM.put(1, Layout);
  EEPROM.put(1+sizeof(Layout), Layout_Arrows);
  //EEPROM.commit();
  return 0;
}

char KBB::ReadFromEEPROM(){
  EEPROM.get(1, Layout);
  EEPROM.get(1+sizeof(Layout), Layout_Arrows);
  return 0;
}


void KBB::begin() 
{
  EEPROM.begin();
  
  unsigned int i;
  
  pinMode(PIN_ADDR_A0, OUTPUT);
  pinMode(PIN_ADDR_A1, OUTPUT);
  pinMode(PIN_ADDR_A2, OUTPUT);

  pinMode(PIN_LED0, OUTPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);

  for (i = 0; i < NUMBER_OF_SEGS; i++) {
    pinMode(pin_map_main[i], INPUT);
  }
  for (i = 0; i < NUMBER_OF_ARROWS; i++) {
    pinMode(pin_map_arrows[i], INPUT_PULLUP);
  }

  if (EEPROM.read(0) != WATERMARK)
  {
    EEPROM_init();
    SaveToEEPROM();
  }
  else{
    ReadFromEEPROM();
  } 
}

void KBB::ChangeSegment(unsigned int seg) 
{
  segment = seg & 0x7;
  digitalWrite(PIN_ADDR_A0, seg & 0x1);
  digitalWrite(PIN_ADDR_A1, seg & 0x2);
  digitalWrite(PIN_ADDR_A2, seg & 0x4);
  delayMicroseconds(50);
}

void KBB::RefreshKeyMap()  
{
  unsigned int i;
  /*The function refresh a segment from the keymap*/
  for (i = 0; i < NUMBER_OF_SEGS; i++) {
    KeyMapMain[segment][i].actual = !digitalRead(pin_map_main[i]);
  }
  for (i = 0; i < NUMBER_OF_ARROWS; i++) {
    KeyMapArrows[i].actual = !digitalRead(pin_map_arrows[i]);
  }
}

void KBB::SaveToPastSegment() 
{
  unsigned int i;
  for (i = 0; i < KEYS_IN_SEGS; i++) {
    KeyMapMain[segment][i].last = KeyMapMain[segment][i].actual;
  }
  for (i = 0; i < NUMBER_OF_ARROWS; i++) {
    KeyMapArrows[i].last = KeyMapArrows[i].actual;
  }
}

bool KBB::CompareLastKeys(struct key_map* keymap, unsigned int len) 
{
  unsigned int index = 0;
  bool ret = false;

  for (index = 0; index < len; index++) {
    keymap[index].press   = false;
    keymap[index].release = false;

    if(keymap[index].last != keymap[index].actual) {
      if(keymap[index].actual) {
        keymap[index].press = true;
      }
      else{
        keymap[index].release = true;
      }
      ret = true;
    }
  }

 return ret;
}

bool KBB::CompareLastKeys() 
{
  return CompareLastKeys(KeyMapMain[segment], NUMBER_OF_SEGS)   ||
         CompareLastKeys(KeyMapArrows,        NUMBER_OF_ARROWS);
}

void KBB::HandleSendChange(struct char_holder* key, bool press) 
{
  if (NULL == key->def) {
    return;
  }

  if (FUNCTION_KEY == key->def) {
    fn_pressed = press;
    return;
  }

  if (fn_pressed || fn_locked) {
    if(press){
      if (key->fn)        SendPress(key->fn);
      if (key->fn_press)  key->fn_press();
    }
    else {
      if (key->fn)          SendRelease(key->fn);
      if (key->fn_release)  key->fn_release();
    }
  }
  else {
    if (win_locked && KEY_LEFT_WIN == key->def) {
      return;
    }

    if(press){
      SendPress(key->def);
    }
    else {
      SendRelease(key->def);
    }
  }
}


void KBB::SendSegment() 
{
  int key;
  for(key = 0; key < KEYS_IN_SEGS; key++) {
    if (KeyMapMain[segment][key].press || KeyMapMain[segment][key].release) {
      this->HandleSendChange(&Layout[segment][key], KeyMapMain[segment][key].press);
    }
  }
  for(key = 0; key < NUMBER_OF_ARROWS; key++) {
    if (KeyMapArrows[key].press || KeyMapArrows[key].release) {
      this->HandleSendChange(&Layout_Arrows[key], KeyMapArrows[key].press);
    }
  }
}

inline void KBB::SendPress(char key){
  Keyboard.press(key);
  SyncMaps();
  
}

inline void KBB::SendRelease(char key){
  Keyboard.release(key);
  SyncMaps();
}

void KBB::SyncMaps(){
  if (Serial.available())
  {
    if (Serial.read() == WATERMARK)
    {
        mapInterface->SyncKeyMap(Layout, Layout, sizeof(Layout));
        mapInterface->SyncArrowMap(Layout_Arrows, Layout_Arrows, sizeof(Layout_Arrows));

        SaveToEEPROM();
    }
  }

}