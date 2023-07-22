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
  MainInterface->ChangeSegment(segment);
  MainInterface->CheckSegment(segment);
  ++segment;
}
