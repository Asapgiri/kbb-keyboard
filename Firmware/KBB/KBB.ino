#include "KBB.h"
#include <Keyboard.h>
#include "KeyboardMacroInterface.h"

static KBB* MainInterface = nullptr;
static KeyboardMacroInterface* ExtensionInterface= nullptr;
static unsigned char segment = 0;

void setup() {
  Serial.begin(115200);
  Keyboard.begin();
  Keyboard.releaseAll();
  ExtensionInterface = new KeyboardMacroInterface();
  ExtensionInterface->Sync();
  MainInterface = new KBB(ExtensionInterface);
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
