#ifndef OutputSwitch_h
    #include <headers/OutputSwitch.h>
#endif

OutputSwitch Led( LedPin, LedActive, 600 );

#ifdef MotorPin
    OutputSwitch Motor( MotorPin, MotorActive );
#endif

namespace UVS {

    void on() {
        Led.on();
        #ifdef MotorPin
            Motor.on();
        #endif
    }

    void off() {
        #ifdef MotorPin
            Motor.off();
        #endif
        Led.off();
    }

    // Use only Led data for time tracking,
    // no point of running motor without light.
    void autoOFF() {
        if (Led.expired()) { off(); }
    }

    // Enable/Disable timer.  
    // Set/Update curing cycle time (in seconds).
    void setTimer(bool count = true, int sec = 0) {
        Led.isTimer = count;
        if (sec > 0) {
            Led.cycle = sec * 1000;
        }
    }
}