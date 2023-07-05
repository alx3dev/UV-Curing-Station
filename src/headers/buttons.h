#ifdef BUTTONS
    #ifndef InputSwitch_h
        #include <headers/InputSwitch.h>
    #endif
    
    // Depending on your board and wiring, you may want to
    // initialize buttons with INPUT_PULLUP or INPUT_PULLDOWN
    void buttons_init() {
        #ifdef ButtonPin
            pinMode(ButtonPin, ButtonMode);
        #endif

        #ifdef Button1Pin
            pinMode(Button1Pin, Button1Mode);
        #endif

        #ifdef Button2Pin
            pinMode(Button2Pin, Button2Mode);
        #endif
    }

    #ifdef ButtonPin
        void buttonPressed() {}
        void buttonReleased() {}
    #endif

    #ifdef Button1Pin
        void button1Pressed() {}
        void button1Released() {}
    #endif

    #ifdef Button2Pin
        void button2Pressed() {}
        void button2Released() {}
    #endif
#endif