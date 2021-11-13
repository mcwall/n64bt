#include <Arduino.h>
#include "n64.h"

N64 controller (13);

void setup() {
    Serial.begin(9600);
    controller.init();
}

void loop() {
    controller.send(0x01);
    controller.get();
    delay(100);

    for (int i = 0; i < 32; i++)
        Serial.print((int)controller.raw_dump[i]);
    Serial.println();
}
