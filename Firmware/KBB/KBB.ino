#include "KBB.h"


static KBB *MainInterface = nullptr;

void setup() {
  Serial.begin(115200);
  MainInterface = new KBB();
  MainInterface->begin();
}

void loop() {

}
