#include <headers/OutputSwitch.h>

OutputSwitch Led( LedPin, LedActive, 600 );

#ifdef MotorPin
    OutputSwitch Motor( MotorPin, MotorActive );
#endif

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
    if (Led.expired()) { uvsOFF(); }
}

// Enable/Disable timer.  
// Set/Update curing cycle time (in seconds).
void uvs_setTimer(bool count = true, int sec = 0) {
    Led.isTimer = count;
    if (sec > 0) {
        Led.cycle = sec * 1000;
    }
}