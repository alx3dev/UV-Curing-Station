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

        unsigned long pressed, prevPressed, released = 0UL;


    public:
        bool isPressed, isReleased = false;
        bool isDoublePress, isLongPress = false;

    InputSwitch(uint8_t in_pin, uint8_t in_mode = INPUT, uint8_t in_type = NC) {
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