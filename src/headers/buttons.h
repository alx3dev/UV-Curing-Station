#ifdef BUTTONS
    #ifndef InputSwitch_h
        #include <headers/InputSwitch.h>
    #endif

namespace UVS {
    // Depending on your board and wiring, you may want to
    // initialize buttons with INPUT_PULLUP or INPUT_PULLDOWN
    void buttons_init()
    {
        #ifdef Button0Pin
            InputSwitch Button0(Button0Pin, Button0Mode, Button0Active);
        #endif

        #ifdef Button1Pin
            InputSwitch Button1(Button1Pin, Button1Mode, Button1Active);
        #endif

        #ifdef Button2Pin
            InputSwitch Button2(Button2Pin, Button2Mode, Button2Active);
        #endif
    }

    #ifdef Button0Pin
        void button0Pressed() {}
        void button0Released() {}
    #endif

    #ifdef Button1Pin
        void button1Pressed() {}
        void button1Released() {}
    #endif

    #ifdef Button2Pin
        void button2Pressed() {}
        void button2Released() {}
    #endif
}
#endif