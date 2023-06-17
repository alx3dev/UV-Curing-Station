// ** Configuration for UV Station ** //

// Define board chip
#define ESP_8266    
//#define ESP_32

// Network (or AP) credentials
const char* SSID = "NETWORK-NAME";
const char* PASS = "NETWORK-PASSWORD";

// UV Led pin
#define LedPin 3

// Default power, uncomment to disable led PWM
#define LedPWM 204

// Uncomment if motor is not connected
#define MotorPin 1

// Default speed, uncomment to disable motor PWM
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