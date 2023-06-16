#define ESP_8266    // define board chip
//#define ESP_32

const char* SSID = "NETWORK-NAME";
const char* PASS = "NETWORK-PASSWORD";

#define LedPin 3
// default power, uncomment to disable pwm
#define LedPWM 204

// uncomment if motor is not connected
#define MotorPin 1
// default speed, uncomment to disable pwm
#define MotorPWM 25.5

// TO-DO: enable buttons
//
//#define ButtonPin_0 2
//#define ButtonPin_1 4

#include <station.h>

#if defined(ButtonPin_0) || defined(ButtonPin_1)
    #define BUTTONS
    #include <buttons.h>
#endif

#if defined(ESP_8266) || defined(ESP_32)
    #define WIFI
    #include <server.h>
#endif