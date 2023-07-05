#ifndef Arduino_h
    #include <Arduino.h>
#endif

#ifndef Config_h
    #include <config.h>
#endif

void setup() {
    #ifdef BUTTONS
        buttons_init();
    #endif
    
    #ifdef LedPWM
        UVS::Led.pwm(LedPWM);
    #endif

    #if defined(MotorPin) && defined(MotorPWM)
        UVS::Motor.pwm(MotorPWM);
    #endif

    #ifdef WIFI
        server_init();
    #endif
}

void loop() {
    #ifdef WIFI
        server.handleClient();
    #endif

    UVS::autoOFF();
}