#ifndef BT_h
#define BT_h
#include "data.h"

class BtController {
    public:
        BtController();
        void init();
        void update(ControllerData status);
        bool isConnected();
    
    private:
        uint32_t lastData;
};
#endif
