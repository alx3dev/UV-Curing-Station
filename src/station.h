#include <DigitalSwitch.h>

DigitalSwitch Led( LedPin, ACTIVE_HIGH, AUTO_OFF, 600 );

#ifdef MotorPin
    DigitalSwitch Motor( MotorPin );
#endif

// Depending on your board and wiring,
// you may want to initialize buttons with INPUT_PULLUP.
void buttons_init(byte mode = INPUT) {
    #ifdef ButtonPin_0
        pinMode(ButtonPin_0, mode);
    #endif

    #ifdef ButtonPin_1
        pinMode(ButtonPin_1, mode);
    #endif
}

void uvsON() {
    Led.turnON();
    #ifdef MotorPin
        Motor.turnON();
    #endif
}

void uvsOFF() {
    #ifdef MotorPin
        Motor.turnOFF();
    #endif
    Led.turnOFF();
}

// Use only Led data for time tracking,
// no point of running motor without light.
void uvs_autoOFF() {
    Led.autoOFF();
}

// Enable/Disable timer.  
// Set/Update curing cycle time (in seconds).
void uvs_setTimer(bool count = true, int sec = 0) {
    Led.timer = count;
    if (sec > 0) {
        Led.cycle = sec * 1000;
    }
}