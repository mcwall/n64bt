#include <Arduino.h>
#include "bt.h"
#include <BleGamepad.h>

BleGamepad bleGamepad("Matt N4 Controller", "Matt Wallick Inc", 100);

BtController::BtController() {
}

void BtController::init() {
    bleGamepad.begin();
}

void BtController::update(uint32_t status) {

}
