#ifdef BUTTONS
    #ifndef InputSwitch_h
        #include <headers/InputSwitch.h>
    #endif

    // Depending on your board and wiring, you may want to
    // initialize buttons with INPUT_PULLUP or INPUT_PULLDOWN
    void buttons_init() {
        #ifdef ButtonPin
            InputSwitch Button(ButtonPin, ButtonMode, ButtonActive);
        #endif

        #ifdef Button1Pin
            InputSwitch Button1(ButtonPin, ButtonMode, ButtonActive);
        #endif

        #ifdef Button2Pin
            InputSwitch Button2(ButtonPin, ButtonMode, ButtonActive);
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