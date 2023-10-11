#include "KBB.h"
#include <Keyboard.h>
#include "KeyboardMapInterface.h"

static KBB* MainInterface = nullptr;
static KeyboardMapInterface* ExtensionInterface= nullptr;
static unsigned char segment = 0;

void setup() {
  //Serial.begin(115200);
  Keyboard.begin();
  Keyboard.releaseAll();
  ExtensionInterface = new KeyboardMapInterface();
  MainInterface = new KBB(ExtensionInterface);
  MainInterface->begin();
}

void loop() {
  int currentMillis = millis();
  MainInterface->ChangeSegment(segment);  //Find the next Target
  MainInterface->RefreshKeyMap();         //Refresh the actually pressed keys map
  if(MainInterface->CompareLastKeys(currentMillis)){   //If it changed
    MainInterface->SendSegment();         //Send the changes to host
    MainInterface->SaveToPastSegment();   //Copy the actual segment to the last
  }

  segment++;
  MainInterface->SyncKeyMap();
}
