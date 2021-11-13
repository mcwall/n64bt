#include <Arduino.h>
#include "data.h"

const double Y_MAX = 109.0;
const double Y_MIN = 112.0;

const double X_MAX = 104.0;
const double X_MIN = 111.0;

ControllerData::ControllerData() {
}

void ControllerData::update(uint32_t rawData) {
    yRaw = rawData & 0xff;
    if (yRaw > 0) {
        y = std::min(1.0, yRaw / Y_MAX);
    } else {
        y = std::max(-1.0, yRaw / Y_MIN);
    }

    rawData >>= 8;

    xRaw = rawData & 0xff;
    if (xRaw > 0) {
        x = std::min(1.0, xRaw / X_MAX);
    } else {
        x = std::max(-1.0, xRaw / X_MIN);
    }
}
