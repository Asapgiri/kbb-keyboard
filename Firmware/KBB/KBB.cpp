#include "KBB.h"
#include <Arduino.h>
#include <Keyboard.h>

static struct char_holder Layout[NUMBER_OF_SEGS][KEYS_IN_SEGS] = {
  {
    { def: KEY_ESC,           fn: '`',  fn_press: NULL, fn_release: NULL },
    { def: 'w',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '4',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '5',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '7',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '9',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '-',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: KEY_BACKSPACE,     fn: NULL, fn_press: NULL, fn_release: NULL }
  },
  {
    { def: '1',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '3',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'r',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '6',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '8',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '0',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '=',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: KEY_PRINT_SCREEN,  fn: NULL, fn_press: NULL, fn_release: NULL }
  },
  {
    { def: 'q',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 's',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'f',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'y',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'i',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'p',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: ']',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: KEY_DELETE,        fn: NULL, fn_press: NULL, fn_release: NULL }
  },
  {
    { def: KEY_TAB,           fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '2',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'e',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 't',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'u',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'o',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '[',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '\\',              fn: NULL, fn_press: NULL, fn_release: NULL }
  },
  {
    { def: 91,                fn: NULL, fn_press: NULL, fn_release: NULL }, // Left WIN
    { def: 'x',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'v',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'h',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'k',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: ';',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: KEY_RIGHT_SHIFT,   fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: KEY_HOME,          fn: NULL, fn_press: NULL, fn_release: NULL }
  },
  {
    { def: KEY_CAPS_LOCK,     fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'a',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'd',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'g',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'j',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'l',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '\'',              fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: KEY_RETURN,        fn: NULL, fn_press: NULL, fn_release: NULL }
  },
  {
    { def: KEY_LEFT_CTRL,     fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: KEY_LEFT_ALT,      fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: ' ',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'n',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: ',',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: KEY_RIGHT_ALT,     fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: FUNCTION_KEY,      fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: KEY_END,           fn: NULL, fn_press: NULL, fn_release: NULL }
  },
  {
    { def: KEY_LEFT_SHIFT,    fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'z',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'c',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'b',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: 'm',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '.',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: '/',               fn: NULL, fn_press: NULL, fn_release: NULL },
    { def: NULL,              fn: NULL, fn_press: NULL, fn_release: NULL }
  }
  
};

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
  pinMode(ADDR_A0, OUTPUT);
  pinMode(ADDR_A1, OUTPUT);
  pinMode(ADDR_A2, OUTPUT);

  pinMode(SEG0, INPUT);
  pinMode(SEG1, INPUT);
  pinMode(SEG2, INPUT);
  pinMode(SEG3, INPUT);
  pinMode(SEG4, INPUT);
  pinMode(SEG5, INPUT);
  pinMode(SEG6, INPUT);
  pinMode(SEG7, INPUT);
}

void KBB::ChangeSegment(unsigned char seg){
  digitalWrite(ADDR_A0, seg & 0x1);
  digitalWrite(ADDR_A1, seg & 0x2);
  digitalWrite(ADDR_A2, seg & 0x4);
  delayMicroseconds(50);
}

void KBB::RefreshActualKeyMap(unsigned char seg){
  /*The function refresh a segment from the keymap*/
  ActualKeyMap[seg][0] = digitalRead(SEG0) == 0;
  ActualKeyMap[seg][1] = digitalRead(SEG1) == 0;
  ActualKeyMap[seg][2] = digitalRead(SEG2) == 0;
  ActualKeyMap[seg][3] = digitalRead(SEG3) == 0;
  ActualKeyMap[seg][4] = digitalRead(SEG4) == 0;
  ActualKeyMap[seg][5] = digitalRead(SEG5) == 0;
  ActualKeyMap[seg][6] = digitalRead(SEG6) == 0;
  ActualKeyMap[seg][7] = digitalRead(SEG7) == 0;
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

void KBB::SendChangesToHost(unsigned char seg) {
  for(unsigned char key = 0; key < KEYS_IN_SEGS; key++) {
    if (NULL == Layout[seg][key].def) {
      continue;
    }

    if (FUNCTION_KEY == Layout[seg][key].def) {
      if(PressKeyMap[seg][key]) {
        fn_pressed = true;
      }
      else if (ReleaseKeyMap[seg][key]) {
        fn_pressed = false;
      }
      continue;
    }

    if (fn_pressed) {
      if(PressKeyMap[seg][key]){
        if (Layout[seg][key].fn)        Keyboard.press(Layout[seg][key].fn);
        if (Layout[seg][key].fn_press)  Layout[seg][key].fn_press();
      }
      else if (ReleaseKeyMap[seg][key]) {
        if (Layout[seg][key].fn)          Keyboard.release(Layout[seg][key].fn);
        if (Layout[seg][key].fn_release)  Layout[seg][key].fn_release();
      }
    }
    else {
      if(PressKeyMap[seg][key]){
        Keyboard.press(Layout[seg][key].def);
      }
      else if (ReleaseKeyMap[seg][key]) {
        Keyboard.release(Layout[seg][key].def);
      }
    }
  }
}
