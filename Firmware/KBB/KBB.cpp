#include "KBB.h"
#include <Arduino.h>
#include <Keyboard.h>

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
    { def: KEY_INSERT,        fn: KEY_PRINT_SCREEN,   fn_press: NULL,         fn_release: NULL }
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Public fields
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

KBB::KBB(){
  fn_pressed = false;
  for(unsigned char seg; seg < NUMBER_OF_SEGS; seg++){
    for(unsigned char key; key < KEYS_IN_SEGS; seg++){
      this->ActualKeyMap[seg][key]=false;
      this->LastKeyMap[seg][key]=false;
      this->PressKeyMap[seg][key]=false;
      this->ReleaseKeyMap[seg][key]=false;
    }
  }
}

KBB::~KBB(){
  /*Nothing to do yet*/
}

void KBB::begin(){
  pinMode(PIN_ADDR_A0, OUTPUT);
  pinMode(PIN_ADDR_A1, OUTPUT);
  pinMode(PIN_ADDR_A2, OUTPUT);

  pinMode(PIN_LED0, OUTPUT);
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);

  pinMode(PIN_SEG0, INPUT);
  pinMode(PIN_SEG1, INPUT);
  pinMode(PIN_SEG2, INPUT);
  pinMode(PIN_SEG3, INPUT);
  pinMode(PIN_SEG4, INPUT);
  pinMode(PIN_SEG5, INPUT);
  pinMode(PIN_SEG6, INPUT);
  pinMode(PIN_SEG7, INPUT);

  pinMode(PIN_ARROW_UP,    INPUT_PULLUP);
  pinMode(PIN_ARROW_DOWN,  INPUT_PULLUP);
  pinMode(PIN_ARROW_LEFT,  INPUT_PULLUP);
  pinMode(PIN_ARROW_RIGHT, INPUT_PULLUP);
}

void KBB::ChangeSegment(unsigned char seg){
  digitalWrite(PIN_ADDR_A0, seg & 0x1);
  digitalWrite(PIN_ADDR_A1, seg & 0x2);
  digitalWrite(PIN_ADDR_A2, seg & 0x4);
  delayMicroseconds(50);
}

void KBB::RefreshActualKeyMap(unsigned char seg){
  /*The function refresh a segment from the keymap*/
  ActualKeyMap[seg][0] = digitalRead(PIN_SEG0) == 0;
  ActualKeyMap[seg][1] = digitalRead(PIN_SEG1) == 0;
  ActualKeyMap[seg][2] = digitalRead(PIN_SEG2) == 0;
  ActualKeyMap[seg][3] = digitalRead(PIN_SEG3) == 0;
  ActualKeyMap[seg][4] = digitalRead(PIN_SEG4) == 0;
  ActualKeyMap[seg][5] = digitalRead(PIN_SEG5) == 0;
  ActualKeyMap[seg][6] = digitalRead(PIN_SEG6) == 0;
  ActualKeyMap[seg][7] = digitalRead(PIN_SEG7) == 0;
}

void KBB::CopyActualToLastSegment(unsigned char seg){
  memcpy(&LastKeyMap[seg][0], &ActualKeyMap[seg][0], KEYS_IN_SEGS);
}

bool KBB::CompareActualAndLastKeys(unsigned char seg){
  unsigned char index = 0;
  bool ret = false;
  while(index < KEYS_IN_SEGS){
    PressKeyMap[seg][index]=false;
    ReleaseKeyMap[seg][index]=false;

    if(LastKeyMap[seg][index] != ActualKeyMap[seg][index]){
      if(ActualKeyMap[seg][index]){
        PressKeyMap[seg][index]=true;
      }
      else{
        ReleaseKeyMap[seg][index]=true;
      }
      ret = true;
      break;
    }
    ++index;
  }
  while(index < KEYS_IN_SEGS){
    PressKeyMap[seg][index]=false;
    ReleaseKeyMap[seg][index]=false;

    if(LastKeyMap[seg][index] != ActualKeyMap[seg][index]){
      if(ActualKeyMap[seg][index]){
        PressKeyMap[seg][index]=true;
      }
      else{
        ReleaseKeyMap[seg][index]=true;
      }
    }
    ++index;
  }
  return ret;
}

void KBB::HandleSendChange(struct char_holder* key, bool press) {
  if (NULL == key->def) {
    return;
  }

  if (FUNCTION_KEY == key->def) {
    fn_pressed = press;
    return;
  }

  if (fn_pressed || fn_locked) {
    if(press){
      if (key->fn)        Keyboard.press(key->fn);
      if (key->fn_press)  key->fn_press();
    }
    else {
      if (key->fn)          Keyboard.release(key->fn);
      if (key->fn_release)  key->fn_release();
    }
  }
  else {
    if (win_locked && KEY_LEFT_WIN == key->def) {
      return;
    }

    if(press){
      Keyboard.press(key->def);
    }
    else {
      Keyboard.release(key->def);
    }
  }
}


void KBB::SendChangesToHost(unsigned char seg) {
  for(unsigned char key = 0; key < KEYS_IN_SEGS; key++) {
    if (PressKeyMap[seg][key] || ReleaseKeyMap[seg][key]) {
      this->HandleSendChange(&Layout[seg][key], PressKeyMap[seg][key]);
    }
  }
}
