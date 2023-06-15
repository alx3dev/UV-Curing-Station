#define ESP_8266
//#define ESP_32

const char* SSID = "NETWORK-NAME";
const char* PASS = "NETWORK-PASSWORD";

#define LedPin 3
#define LedPWM 204

#define MotorPin 1
#define MotorPWM 25.5

//#define ButtonPin_0 4
//#define ButtonPin_1 5

#include <station.h>

#if defined(ButtonPin_0) || defined(ButtonPin_1)
    #define BUTTONS
    #include <buttons.h>
#endif

#if defined(ESP_8266) || defined(ESP_32)
    #define WIFI
    #include <server.h>
#endif