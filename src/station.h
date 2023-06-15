#include <DigitalSwitch.h>

DigitalSwitch Led( LedPin, ACTIVE_HIGH, AUTO_OFF, 600 );

#ifdef MotorPin
    DigitalSwitch Motor( MotorPin );
#endif


void buttons_init(byte mode = INPUT_PULLUP) {
    #ifdef ButtonPin_0
        pinMode(ButtonPin_0, mode);
    #endif

    #ifdef ButtonPin_1
        pinMode(ButtonPin_1, mode);
    #endif
}

void uvsON() {
    Led.turnON();
    #ifdef MotorMosfetPin
        Motor.turnON();
    #endif
}

void uvsOFF() {
    #ifdef MotorMosfetPin
        Motor.turnOFF();
    #endif
    Led.turnOFF();
}

void uvs_autoOFF() {
    Led.autoOFF();
}

void uvs_setTimer(bool count = true, int sec = 0) {
    Led.timer = count;
    if (sec > 0) {
        Led.pause = sec * 1000;
    }
}