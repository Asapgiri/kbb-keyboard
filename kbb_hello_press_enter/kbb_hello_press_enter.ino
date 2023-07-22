#include <Keyboard.h>

#define ADDRESS0  7   // phisical pin 1
#define ADDRESS1  19  // phisical pin 37
#define ADDRESS2  18  // phisical pin 36

#define SEG7      13  // phisical pin 32

bool enter_press, stored_enter_press;

void read_all_pins(void) {
    bool input;
    int i;
    //for (
}

void setup() {
    // put your setup code here, to run once:
    //Serial.begin(9600);
    Keyboard.begin();
    
    pinMode(SEG7, INPUT);
    pinMode(ADDRESS0, OUTPUT);
    pinMode(ADDRESS1, OUTPUT);
    pinMode(ADDRESS2, OUTPUT);
    digitalWrite(ADDRESS0, HIGH);
    digitalWrite(ADDRESS1, LOW);
    digitalWrite(ADDRESS2, HIGH);
}

void loop() {
    // put your main code here, to run repeatedly:
    enter_press = digitalRead(SEG7);
    //Serial.println(" BKK keyboard hello!");
    
    if (stored_enter_press != enter_press) {
        stored_enter_press = enter_press;
        if (enter_press) {
            //Serial.println("Enter has been released.");
            Keyboard.release('\r');
            Keyboard.release('\n');
        }
        else {
            //Serial.println("Enter has been PRESSED.");
            Keyboard.press('\r');
            Keyboard.press('\n');
        }
    }
    
    //delay(1000);
}
