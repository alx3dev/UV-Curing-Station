#ifndef Arduino_h
    #include <Arduino.h>    // make VScode happy
#endif

#define NC LOW
#define NO HIGH

class InputSwitch {

    private:
        byte pin;
        byte mode;
        byte type;

    public:
        bool isPressed, isReleased = false;
        bool isDoublePress, isLongPress = false;

        unsigned long pressed, prevPressed, released = 0UL;

    InputSwitch(byte in_pin, byte in_mode = INPUT, byte in_type = NC) {
        pin = in_pin;
        mode = in_mode;
        type = in_type;

        pinMode(pin, mode);
    }

    void handleISR() {
        if (inputActive()) {
            isPressed = true;
            prevPressed = pressed;
            pressed = millis();
            isDoublePress = pressed - prevPressed < 500 ? true : false;
        } else {
            isReleased = true;
            released = millis();
            isLongPress = released - pressed > 800 ? true : false;
        }
    }

    void resetStatus() {
        isPressed = false;
        isReleased = false;
        isDoublePress = false;
        isLongPress = false;
    }

    bool inputActive() {
        return digitalRead(pin) == type;
    }
};