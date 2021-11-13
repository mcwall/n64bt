#include <Arduino.h>
#include "n64.h"
#include <BleGamepad.h> 

N64 nController (13);
BleGamepad btController("Matt N4 Controller", "Matt Wallick Inc", 100);

void setup() {
    Serial.begin(9600);
    nController.init();
}

void loop() {
    uint32_t test = nController.get();
    int8_t y = test & 0xff;

    // for (int i = 31; i >= 0; i--)
    //     Serial.print((test >> i) & 1 ? 1 : 0);

    Serial.println(y);
    delay(100);
}
