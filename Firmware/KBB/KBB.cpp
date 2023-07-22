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
}

void KBB::CheckSegment(unsigned char seg){
  unsigned char PIN_SEG0 = digitalRead(SEG0);
  unsigned char PIN_SEG1 = digitalRead(SEG1);
  unsigned char PIN_SEG2 = digitalRead(SEG2);
  unsigned char PIN_SEG3 = digitalRead(SEG3);
  unsigned char PIN_SEG4 = digitalRead(SEG4);
  unsigned char PIN_SEG5 = digitalRead(SEG5);
  unsigned char PIN_SEG6 = digitalRead(SEG6);
  unsigned char PIN_SEG7 = digitalRead(SEG7);
  if(seg == 0){ 

  }
  if(seg == 1){

  }
  if(seg == 2){

  }
  if(seg == 3){
  }
  if(seg == 4){
  }
  if(seg == 5){
  }
  if(seg == 6){
  }
  if(seg == 7){
  }
}
