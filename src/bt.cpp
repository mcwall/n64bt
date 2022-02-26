#include <Arduino.h>
#include "bt.h"
#include <BleGamepad.h>

BleGamepad controller("Matt N64 Controller", "Matt Wallick Inc", 100);

BtController::BtController() {
}

void BtController::init() {
    controller.begin(
        11,     //Buttons
        1,      // Hat switch
        true,   // X-Axis
        true,   // Y-Axis
        false,  // Z-Axis
        false,  // Rz-Axis
        false,  // Rx-Axis
        false,  // Ry-Axis
        false,  // Slider1
        false   // Slider2
    );
    controller.setAutoReport(false);
}

namespace {
    signed char getHat(ControllerData data) {
        if (data.dUp) {
            if (data.dLeft) 
                return HAT_UP_LEFT;
            else if (data.dRight)
                return HAT_UP_RIGHT;
            return HAT_UP;
        }

        if (data.dDown) {
            if (data.dLeft) 
                return HAT_DOWN_LEFT;
            else if (data.dRight)
                return HAT_DOWN_RIGHT;
            return HAT_DOWN;
        }

        if (data.dLeft)
            return HAT_LEFT;
        if (data.dRight)
            return HAT_RIGHT;
        return HAT_CENTERED;
    }
}

void BtController::update(ControllerData data) {
    if (data.raw == lastData || !controller.isConnected()) {
        return;
    }

    controller.setHat(getHat(data));
    controller.setLeftThumb(data.x * INT16_MAX, data.y * INT16_MAX);

    bool dataButtons[] = {
        data.a, data.b, data.z, data.l, data.r,
        data.cUp, data.cRight, data.cDown, data.cLeft,
        data.start, data.reset
    };
    for (int i = 0; i < 11; i++) {
        if (dataButtons[i])
            controller.press(i+1);
        else
            controller.release(i+1);
    }

    lastData = data.raw;
    controller.sendReport();
}

bool BtController::isConnected() {
    return controller.isConnected();
}
