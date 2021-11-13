#include <Arduino.h>
#include <stdint.h>
#include "n64.h"
#include "bt.h"
#include "data.h"

N64Controller nController(13);
BtController btController;
ControllerData controllerData;

void setup() {
    Serial.begin(9600);
    nController.init();
    btController.init();
}

void loop() {
    
    // for (int i = 31; i >= 0; i--)
    //     Serial.print((test >> i) & 1 ? 1 : 0);

    controllerData.update(nController.status());
    Serial.println(controllerData.y);
    delay(100);
}
