#include <Arduino.h>
#include "data.h"

const double Y_MAX = 102.0;
const double Y_MIN = 111.0;

const double X_MAX = 104.0;
const double X_MIN = 111.0;

ControllerData::ControllerData() {
}

void ControllerData::update(uint32_t rawData) {
    // All bits set indicates something went wrong while polling latest state from controller, don't update state on this cycle
    if (rawData == 0xffffffff)
        return;

    // Y AXIS
    yRaw = rawData & 0xff;
    if (yRaw > 0) {
        y = std::min(1.0, yRaw / Y_MAX);
    } else {
        y = std::max(-1.0, yRaw / Y_MIN);
    }
    // Y is upside down for some reason, so flip it
    y = y * -1.0;

    // X AXIS
    rawData >>= 8;
    xRaw = rawData & 0xff;
    if (xRaw > 0) {
        x = std::min(1.0, xRaw / X_MAX);
    } else {
        x = std::max(-1.0, xRaw / X_MIN);
    }

    // C BUTTONS
    rawData >>= 8;
    reset = (rawData >> 7) & 1;
    l = (rawData >> 5) & 1;
    r = (rawData >> 4) & 1;
    cUp = (rawData >> 3) & 1;
    cDown = (rawData >> 2) & 1;
    cLeft = (rawData >> 1) & 1;
    cRight = (rawData >> 0) & 1;

    // D BUTTONS
    rawData >>= 8;
    a = (rawData >> 7) & 1;
    b = (rawData >> 6) & 1;
    z = (rawData >> 5) & 1;
    start = (rawData >> 4) & 1;
    dUp = (rawData >> 3) & 1;
    dDown = (rawData >> 2) & 1;
    dLeft = (rawData >> 1) & 1;
    dRight = (rawData >> 0) & 1;
}
