#ifndef UVS
    #define ESP_8266
    //#define ESP_32

    const char* SSID = "NETWORK-NAME";
    const char* PASS = "NETWORK-PASSWORD";

    #define MotorMosfetPin 1
    #define LedMosfetPin 3

    #include <station.h>

    #if defined(ESP_8266) || defined(ESP_32)
        #include <server.h>
    #endif
  
    #define UVS
#endif


void setup() {
    #if defined(ESP_8266) || defined(ESP_32)
        server_init();
    #endif

    // activate PWM
    Motor.pwm(25.5); // 10%
    //Led.pwm(204);    // 80%
}

void loop() {
    #if defined(ESP_8266) || defined(ESP_32)
        server.handleClient();
    #endif

    uvs_autoOFF();
}