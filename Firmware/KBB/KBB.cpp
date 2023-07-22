#include "KBB.h"
#include <Arduino.h>
#include <Keyboard.h>

static unsigned char Layout[NUMBER_OF_SEGS][KEYS_IN_SEGS] = {
  {'0', '1', '2', '3', '4', '5', '6', '7'},
  {'0', '1', '2', '3', '4', '5', '6', '7'},
  {'0', '1', '2', '3', '4', '5', '6', '7'},
  {'0', '1', '2', '3', '4', '5', '6', '7'},
  {'0', '1', '2', '3', '4', '5', '6', '7'},
  {'0', '1', '2', '3', '4', '5', '6', '7'},
  {'0', '1', '2', '3', '4', '5', '6', '7'},
  {'0', '1', '2', '3', '4', '5', '6', '7'},
};

KBB::KBB(){
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
  if(seg == 0){
    digitalWrite(ADDR_A0, LOW);
    digitalWrite(ADDR_A1, LOW);
    digitalWrite(ADDR_A2, LOW);
  }
  if(seg == 1){
    digitalWrite(ADDR_A0, HIGH);
    digitalWrite(ADDR_A1, LOW);
    digitalWrite(ADDR_A2, LOW);
  }
  if(seg == 2){
    digitalWrite(ADDR_A0, LOW);
    digitalWrite(ADDR_A1, HIGH);
    digitalWrite(ADDR_A2, LOW);
  }
  if(seg == 3){
    digitalWrite(ADDR_A0, HIGH);
    digitalWrite(ADDR_A1, HIGH);
    digitalWrite(ADDR_A2, LOW);
  }
  if(seg == 4){
    digitalWrite(ADDR_A0, LOW);
    digitalWrite(ADDR_A1, LOW);
    digitalWrite(ADDR_A2, HIGH);
  }
  if(seg == 5){
    digitalWrite(ADDR_A0, HIGH);
    digitalWrite(ADDR_A1, LOW);
    digitalWrite(ADDR_A2, HIGH);
  }
  if(seg == 6){
    digitalWrite(ADDR_A0, LOW);
    digitalWrite(ADDR_A1, HIGH);
    digitalWrite(ADDR_A2, HIGH);
  }
  if(seg == 7){
    digitalWrite(ADDR_A0, HIGH);
    digitalWrite(ADDR_A1, HIGH);
    digitalWrite(ADDR_A2, HIGH);
  }
  //delay(1000);
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
  unsigned char index;
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
void KBB::SendChangesToHost(unsigned char seg){
  for(unsigned char key = 0; key < KEYS_IN_SEGS; key++){
    if(PressKeyMap[seg][key]){
      Keyboard.press(Layout[seg][key]);
    }
    else if (ReleaseKeyMap[seg][key]){
      Keyboard.release(Layout[seg][key]);
    }
  }
}
