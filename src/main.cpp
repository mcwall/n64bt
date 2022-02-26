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

TaskHandle_t taskMain;
TaskHandle_t taskPoll;

bool ledState;
unsigned long lastLedBlinkMs;

void doMain( void * pvParameters ){
    while (1) {
        btController.update(controllerData);
        vTaskDelay(9);
    }
}

void doPoll( void * pvParameters ){
    while (1) {
        controllerData.update(nController.status());
        vTaskDelay(4);
    }
}

void setup() {
    Serial.begin(9600);
    nController.init();
    btController.init();

    ledState = true;
    lastLedBlinkMs = millis();
    // pinMode(LED_PIN, OUTPUT);
    // digitalWrite(LED_PIN, ledState);

    xTaskCreatePinnedToCore(
                    doMain,
                    "TaskMain",
                    100000,
                    NULL,
                    1,
                    &taskMain,
                    0);

    // char * taskStatuses = (char *) malloc(10000000);
    // vTaskGetRunTimeStats(taskStatuses);
    // Serial.println(taskStatuses);

     xTaskCreatePinnedToCore(
                    doPoll,
                    "TaskPoll",
                    10000,
                    NULL,
                    1,
                    &taskPoll,
                    1);
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
    
    // btController.update(controllerData);

    // debugOutput();
    // Serial.println("foo");
    // Serial.println(btController.isConnected());
    // btController.update(controllerData);
    // delay(500);
}

