#if defined(UVS_BUTTONS) && !defined(UVS_BUTTONS_H)
#define UVS_BUTTONS_H

#include <headers/InputSwitch.h>

namespace UVS {

#ifdef Button0Pin
  InputSwitch Button0(Button0Pin, Button0Mode, Button0Active);
#endif

#ifdef Button1Pin
  InputSwitch Button1(Button1Pin, Button1Mode, Button1Active);
#endif

#ifdef Button2Pin
  InputSwitch Button2(Button2Pin, Button2Mode, Button2Active);
#endif

#ifdef Button0Pin
    void button0LongPressed() {
        UVS::Off();
    }

    void button0Released() {
        UVS::On();
    }
#endif

#ifdef Button1Pin
    void button1Pressed() {}
    void button1Released() {}
#endif

#ifdef Button2Pin
    void button2Pressed() {}
    void button2Released() {}
#endif

void processButtonPress() {
    #ifdef Button0Pin
        if (Button0.isLongPressed) {
            button0LongPressed();
            Button0.statusReset();
        }
        else if (Button0.isReleased) {
            button0Released();
            Button0.statusReset();
        }
    #endif

    #ifdef Button1Pin
        if (Button1.isReleased) {
            button1Released();
            Button1.statusReset();
        }
    #endif
}
}

#endif