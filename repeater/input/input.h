/** @file */

#ifndef INPUT_H
#define INPUT_H

#include "../types.h"

#define HIGH 0x1
#define LOW  0x0
#define INPUT 0x0
#define OUTPUT 0x1


class AbstractInputHandler
{
    public:
    byte pin_;

    AbstractInputHandler(byte pin) {
        pin_ = pin;
    }

    virtual void setup(void) = 0;
    virtual void update(void) = 0;

    virtual void setPinMode(byte mode) {
        pinMode(pin_, mode);
    };

    virtual void writeDigital(byte value) {
        digitalWrite(pin_, value);
    };

    virtual int readDigital() {
        return digitalRead(pin_);
    };

    virtual unsigned long getTimestamp() {
        return millis();
    };

    virtual int readAnalog() {
        return analogRead(pin_);
    };
};
#endif
