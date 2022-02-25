#include <Arduino.h>
#include <stdint.h>
#include "n64.h"
#include "bt.h"
#include "data.h"

#define DATA_PIN 26
#define LED_PIN 33
#define LED_BLINK_PERIOD 1000

N64Controller nController(DATA_PIN);
BtController btController;
ControllerData controllerData;

bool ledState;
unsigned long lastLedBlinkMs;

void setup() {
    Serial.begin(9600);
    nController.init();
    // btController.init();

    ledState = true;
    lastLedBlinkMs = millis();
    // pinMode(LED_PIN, OUTPUT);
    // digitalWrite(LED_PIN, ledState);
}

void debugOutput() {
    Serial.print(controllerData.a);
    Serial.print(controllerData.b);
    Serial.print(controllerData.z);
    Serial.print(controllerData.l);
    Serial.print(controllerData.r);

    Serial.println();
    Serial.print(controllerData.cUp);
    Serial.print(controllerData.cDown);
    Serial.print(controllerData.cLeft);
    Serial.print(controllerData.cRight);

    Serial.println();
    Serial.print(controllerData.dUp);
    Serial.print(controllerData.dDown);
    Serial.print(controllerData.dLeft);
    Serial.print(controllerData.dRight);

    Serial.println();
    Serial.print(controllerData.start);
    Serial.print(controllerData.reset);

    Serial.println();
    Serial.println();
}

void loop() {
    // if (!btController.isConnected()) {
    //     unsigned long now = millis();
    //     if (now - lastLedBlinkMs >= LED_BLINK_PERIOD) {
    //         lastLedBlinkMs = now;
    //         ledState = !ledState;
    //         digitalWrite(LED_PIN, ledState);
    //     }

    //     return;
    // }

    // digitalWrite(LED_PIN, HIGH);
    int newStatus = nController.status();
    int debugStatus = (newStatus & 0xffff0000) >> 16;
    if (debugStatus > 0)
        Serial.println(debugStatus);
    controllerData.update(newStatus);
    // btController.update(controllerData);

    delay(4);
    // debugOutput();
    // Serial.println(controllerData.x);
}

