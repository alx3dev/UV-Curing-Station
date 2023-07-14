#ifndef UVS_INPUT_SWITCH_H
#define UVS_INPUT_SWITCH_H

#ifndef Arduino_h
#include <Arduino.h>
#endif

namespace UVS {
    
#define NC LOW
#define NO HIGH

class InputSwitch {

private:
    const uint8_t pin;
    const uint8_t mode;
    const uint8_t type;

    unsigned long pressed_m, released_m = 0UL;

public:
    bool isPressed, isLongPressed, isReleased = false;

    InputSwitch(uint8_t in_pin, uint8_t in_mode = INPUT, uint8_t in_type = NC) : pin(in_pin), mode(in_mode), type(in_type)
    {
        pinMode(pin, mode);
    }

    bool inputActive()
    {
        return digitalRead(pin) == type;
    }

    void handleISR()
    {
        if (inputActive()) {
            pressed();
            pressed_m = millis();
        } else {
            released();
            released_m = millis();
            longPressed(released_m - pressed_m > 800);
        }
    }

    void pressed(bool status = true) { isPressed = status; }

    void released(bool status = true) { isReleased = status; }

    void longPressed(bool status = true) { isLongPressed = status; }

    void statusReset()
    {
        pressed(false);
        released(false);
        longPressed(false);
    }
};
}

#endif