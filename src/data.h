#ifndef CONTROLLER_DATA_h
#define CONTROLLER_DATA_h
#include <stdint.h>

class ControllerData {
    public:
        bool a;
        bool b;
        bool z;
        bool l;
        bool r;
        bool start;
        bool reset;

        bool cUp;
        bool cDown;
        bool cLeft;
        bool cRight;

        bool dUp;
        bool dDown;
        bool dLeft;
        bool dRight;

        double x;
        double y;

        int8_t xRaw;
        int8_t yRaw;

        uint32_t raw;

        ControllerData();
        void update(uint32_t rawData);
}; 

#endif
