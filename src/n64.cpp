#include <Arduino.h>
#include "n64.h"

#define PIN 13
#define PIN_BIT BIT(PIN)

#define NOP asm volatile ("nop\n")
#define NOP5 NOP;NOP;NOP;NOP;NOP;
#define NOP10 NOP5;NOP5;
#define NOP50 NOP10;NOP10;NOP10;NOP10;NOP10;
#define NOP240 NOP50;NOP50;NOP50;NOP50;NOP10;NOP10;NOP10;

#define ONE_MICROSECOND NOP240;
#define TRHEE_MICROSECOND ONE_MICROSECOND;ONE_MICROSECOND;ONE_MICROSECOND;

#define PIN_QUERY ((REG_READ(GPIO_IN_REG) & PIN_BIT) >> PIN)

N64Controller::N64Controller(unsigned char serialPin) {

}

void N64Controller::init() {
    pinMode(PIN, INPUT);
    REG_WRITE ( GPIO_ENABLE_REG, PIN_BIT ) ;
    REG_WRITE ( GPIO_OUT_W1TS_REG, PIN_BIT ) ; // High
    
    unsigned char initialize = 0x00;
    unsigned char poll = 0x01;

    noInterrupts();
    send(poll);
    interrupts();
}

uint32_t N64Controller::status() {
    noInterrupts();
    send(0x01);
    uint32_t state = read();
    interrupts();
    return state;
}

void N64Controller::send(unsigned char command) {
    char bits = 8;
        bits=8;
send_loop:
    {
        REG_WRITE ( GPIO_OUT_W1TC_REG, PIN_BIT ) ; // Low
        if (command >> 7) {
            ONE_MICROSECOND;
            REG_WRITE ( GPIO_OUT_W1TS_REG, PIN_BIT ) ; // High
            ONE_MICROSECOND;ONE_MICROSECOND;ONE_MICROSECOND;
        } else {
            ONE_MICROSECOND;ONE_MICROSECOND;ONE_MICROSECOND;
            REG_WRITE ( GPIO_OUT_W1TS_REG, PIN_BIT ) ; // High
            ONE_MICROSECOND;
        }

        --bits;
        NOP10;
        if (bits != 0) {
            command <<= 1;
            goto send_loop;
        }
    }

    REG_WRITE ( GPIO_OUT_W1TC_REG, PIN_BIT ) ; // Low
    NOP240;
    REG_WRITE ( GPIO_OUT_W1TS_REG, PIN_BIT ) ; // High
}

uint32_t N64Controller::read() {
    unsigned char timeout;
    int bits = 0;
    int count = 32;

read_loop:

    // Wait for pin to go low
    timeout = 400;
    while (PIN_QUERY) {
        if (!--timeout)
            return 0;
    }
    
    ONE_MICROSECOND;ONE_MICROSECOND;
    bits <<= 1;
    bits |= PIN_QUERY;
    if (--count == 0)
        return bits;

    // Wait for pin to go high
    timeout = 400;
    while (!PIN_QUERY) {
        if (!--timeout)
            return 0;
    }
    goto read_loop;
}
