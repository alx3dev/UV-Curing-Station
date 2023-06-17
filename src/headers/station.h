#include <headers/OutputSwitch.h>

OutputSwitch Led( LedPin, ACTIVE_HIGH, AUTO_OFF, 600 );

#ifdef MotorPin
    OutputSwitch Motor( MotorPin );
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