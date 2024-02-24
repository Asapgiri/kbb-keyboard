#include "KBB.h"
#include <Keyboard.h>

static KBB* MainInterface = nullptr;
static unsigned char segment = 0;

void setup() {
  Keyboard.begin();
  Keyboard.releaseAll();
  MainInterface = new KBB();
  MainInterface->begin();
}

void loop() {
  MainInterface->ChangeSegment(segment);  //Find the next Target
  MainInterface->RefreshKeyMap();         //Refresh the actually pressed keys map
  if(MainInterface->CompareLastKeys()){   //If it changed
    MainInterface->SendSegment();         //Send the changes to host
    MainInterface->SaveToPastSegment();   //Copy the actual segment to the last
  }
  
  segment++;
}
