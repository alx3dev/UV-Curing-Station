#ifndef Arduino_h
    #include <Arduino.h>
#endif

#ifdef BUTTONS
    // Depending on your board and wiring, you may want to
    // initialize buttons with INPUT_PULLUP or INPUT_PULLDOWN
    void buttons_init(byte mode = INPUT) {
        #ifdef ButtonPin
            pinMode(ButtonPin, ButtonMode);
        #endif

        #ifdef Button1Pin
            pinMode(Button1Pin, Button1Mode);
        #endif
    }

    void buttonPressed() {

    }

    void buttonReleased() {

    }

    void button1Pressed() {

    }

    void button1Released() {

    }
#endif