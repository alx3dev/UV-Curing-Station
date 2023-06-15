#ifndef UVS
    #include <Arduino.h>
    #include <config.h>
    #define UVS
#endif


void setup() {
    #ifdef WIFI
        server_init();
    #endif

    #ifdef BUTTONS
        buttons_init();
    #endif
    
    #ifdef LedPWM
        Led.pwm(LedPWM);
    #endif

    #ifdef MotorPWM
        Motor.pwm(MotorPWM);
    #endif
}

void loop() {
    #ifdef WIFI
        server.handleClient();
    #endif

    uvs_autoOFF();
}