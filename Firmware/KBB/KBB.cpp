#include "KBB.h"
#include <Arduino.h>
#include <Keyboard.h>

KBB::KBB(){
  this->CapsLockActualState = false;
  this->NumLockActualState = false;
  this->ScrollLockActualState = false;

  this->CapsLockState = false;
  this->NumLockState = false;
  this->ScrollLockState = false;
}
KBB::~KBB(){
  /*Nothing to do yet*/
}
void KBB::begin(){
  pinMode(ADDR_A0, OUTPUT);
  pinMode(ADDR_A1, OUTPUT);
  pinMode(ADDR_A2, OUTPUT);
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
}

void KBB::CheckSegment(unsigned char seg){
}
