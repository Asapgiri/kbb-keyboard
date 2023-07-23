#include "KBB.h"
#include <Arduino.h>
#include <Keyboard.h>


static unsigned char Layout[NUMBER_OF_SEGS][KEYS_IN_SEGS] = {
  {'A', '1', '2', '3', '4', '5', '6', '7'},
  {'B', '1', '2', '3', '4', '5', '6', '7'},
  {'C', '1', '2', '3', '4', '5', '6', '7'},
  {'D', '1', '2', '3', '4', '5', '6', '7'},
  {'E', '1', '2', '3', '4', '5', '6', '7'},
  {'F', '1', '2', '3', '4', '5', '6', '7'},
  {'G', '1', '2', '3', '4', '5', '6', '7'},
  {'H', '1', '2', '3', '4', '5', '6', '7'},
};

KBB::KBB(){
  for(unsigned char seg; seg < NUMBER_OF_SEGS; seg++){
    for(unsigned char key; key < KEYS_IN_SEGS; seg++){
      this->ActualKeyMap[(seg * KEYS_IN_SEGS) + key]  = false;
      this->LastKeyMap[(seg * KEYS_IN_SEGS) + key]    = false;
      this->PressKeyMap[(seg * KEYS_IN_SEGS) + key]   = false;
      this->ReleaseKeyMap[(seg * KEYS_IN_SEGS) + key] = false;
    }
  }
}



KBB::~KBB(){
  /*Nothing to do yet*/
}

void KBB::begin() {
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
  delay(1);
}

void KBB::RefreshActualKeyMap(unsigned char seg) {
  /*The function refresh a segment from the keymap*/
  this->ActualKeyMap[(seg * KEYS_IN_SEGS)]     = digitalRead(SEG0) == 0;
  this->ActualKeyMap[(seg * KEYS_IN_SEGS) + 1] = digitalRead(SEG1) == 0;
  this->ActualKeyMap[(seg * KEYS_IN_SEGS) + 2] = digitalRead(SEG2) == 0;
  this->ActualKeyMap[(seg * KEYS_IN_SEGS) + 3] = digitalRead(SEG3) == 0;
  this->ActualKeyMap[(seg * KEYS_IN_SEGS) + 4] = digitalRead(SEG4) == 0;
  this->ActualKeyMap[(seg * KEYS_IN_SEGS) + 5] = digitalRead(SEG5) == 0;
  this->ActualKeyMap[(seg * KEYS_IN_SEGS) + 6] = digitalRead(SEG6) == 0;
  this->ActualKeyMap[(seg * KEYS_IN_SEGS) + 7] = digitalRead(SEG7) == 0;
}

void KBB::CopyActualToLastSegment(unsigned char seg) {
  memcpy(&this->LastKeyMap[seg * KEYS_IN_SEGS], &this->ActualKeyMap[seg * KEYS_IN_SEGS], KEYS_IN_SEGS);
}


bool KBB::CompareActualAndLastKeys(unsigned char seg){
  unsigned char index = 0;
  bool ret = false;

  while(index < KEYS_IN_SEGS){
    this->PressKeyMap[(seg * KEYS_IN_SEGS) + index]   = false;
    this->ReleaseKeyMap[(seg * KEYS_IN_SEGS) + index] = false;

    if(this->LastKeyMap[(seg * KEYS_IN_SEGS) + index] != this->ActualKeyMap[(seg * KEYS_IN_SEGS) + index]){
      if(ActualKeyMap[(seg * KEYS_IN_SEGS) + index]){
        this->PressKeyMap[(seg * KEYS_IN_SEGS) + index]=true;
      }
      else{
        this->ReleaseKeyMap[(seg * KEYS_IN_SEGS) + index]=true;
      }
      ret = true;
      ++index;
      break;
    }
    ++index;
  }

  while(index < KEYS_IN_SEGS){
    this->PressKeyMap[(seg * KEYS_IN_SEGS) + index]=false;
    this->ReleaseKeyMap[(seg * KEYS_IN_SEGS) + index]=false;
    
    if(this->LastKeyMap[(seg * KEYS_IN_SEGS) + index] != this->ActualKeyMap[(seg * KEYS_IN_SEGS) + index]){
      if(this->ActualKeyMap[(seg * KEYS_IN_SEGS) + index]){
        this->PressKeyMap[(seg * KEYS_IN_SEGS) + index]=true;
      }
      else{
        this->ReleaseKeyMap[(seg * KEYS_IN_SEGS) + index]=true;
      }
    }
    ++index;
  }

  return ret;
}


void KBB::SendChangesToHost(unsigned char seg){
  for(unsigned char key = 0; key < KEYS_IN_SEGS; key++){
    if(this->PressKeyMap[(seg * KEYS_IN_SEGS) + key]){
      //Keyboard.press(Layout[seg][key]);
      Serial.print(seg);
      Serial.print(", ");
      Serial.print(key);
      Serial.println();
    }
    else if (this->ReleaseKeyMap[(seg * KEYS_IN_SEGS) + key]){
      //Keyboard.release(Layout[seg][key]);
      
    }
  }
}
