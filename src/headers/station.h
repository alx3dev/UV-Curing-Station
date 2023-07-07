#ifndef OutputSwitch_h
    #include <headers/OutputSwitch.h>
#endif

namespace UVS {

    OutputSwitch Led( LedPin, LedActive, 600 );

    #ifdef MotorPin
        OutputSwitch Motor( MotorPin, MotorActive );
    #endif

    // All settings goes here, to be called in setup()
    void init()
    {
        #ifdef BUTTONS
            buttons_init();
        #endif
    
        #ifdef LedPWM
            Led.pwm_init(0, 8, 5000, LedPWM);
        #endif

        #if defined(MotorPin) && defined(MotorPWM)
            Motor.pwm_init(0, 8, 5000, MotorPWM);
        #endif

        #ifdef WIFI
            server_init();
        #endif
    }

    // Turn station ON    
    void on()
    {
        Led.on();
        #ifdef MotorPin
            Motor.on();
        #endif
    }

    // Turn station OFF
    void off()
    {
        #ifdef MotorPin
            Motor.off();
        #endif
        Led.off();
    }

    // Use only Led data for time tracking,
    // no point of running motor without light.
    void autoOFF()
    {
        if (Led.expired()) { off(); }
    }

    // Enable/Disable timer.  
    // Set/Update curing cycle time (in seconds).
    void setTimer(bool status = true, uint16_t sec = 0)
    {
        Led.setTimer(status, sec);
    }
}