#include "KBB.h"
#include <Keyboard.h>

static KBB *MainInterface = nullptr;
static unsigned char segment = 0;

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  MainInterface = new KBB();
  MainInterface->begin();
}

void loop() {
  MainInterface->ChangeSegment(segment);                //Find the next Target
  MainInterface->RefreshActualKeyMap(segment);          //Refresh the actually pressed keys map
  if(MainInterface->CompareActualAndLastKeys(segment)){ //If it changed
    MainInterface->SendChangesToHost(segment);          //Send the changes to host
    MainInterface->CopyActualToLastSegment(segment);    //Copy the actual segment to the last
  }
  ++segment;
}
