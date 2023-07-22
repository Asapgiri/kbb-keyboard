#include "KBB.h"
#include <Arduino.h>

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