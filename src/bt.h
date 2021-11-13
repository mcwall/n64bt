#ifndef BT_h
#define BT_h
#include <stdint.h>

class BtController {
    public:
        BtController();
        void init();
        void update(uint32_t status);
};
#endif
