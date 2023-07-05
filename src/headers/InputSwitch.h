#ifndef Arduino_h
    #include <Arduino.h>    // make VScode happy
#endif

#define NC LOW
#define NO HIGH

class InputSwitch {

    private:
        uint8_t pin;
        uint8_t mode;
        uint8_t type;

        unsigned long pressed_m, prevPressed_m, released_m = 0UL;

    public:
        bool isPressed, isReleased = false;
        bool isDoublePressed, isLongPressed = false;

    InputSwitch(uint8_t in_pin, uint8_t in_mode = INPUT, uint8_t in_type = NC) {
        pin = in_pin;
        mode = in_mode;
        type = in_type;

        pinMode(pin, mode);
    }

    bool inputActive() {
        return digitalRead(pin) == type;
    }

    void handleISR() {
        if (inputActive()) {
            pressed();
            prevPressed_m = pressed_m;
            pressed_m = millis();
            isDoublePressed = pressed_m - prevPressed_m < 500 ? true : false;
        } else {
            released();
            released_m = millis();
            isLongPressed = released_m - pressed_m > 800 ? true : false;
        }
    }

    void pressed(bool status = true) { isPressed = status; }

    void released(bool status = true) { isReleased = status; }

    void doublePressed(bool status = true) { isDoublePressed = status; }

    void longPressed(bool status = true) { isLongPressed = status; }

    void resetStatus() {
        pressed(false);
        released(false);
        doublePressed(false);
        longPressed(false);
    }
};

#define InputSwitch_h