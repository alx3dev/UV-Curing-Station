// ** Configuration for UV Station ** //

#define ESP_8266 // Define board chip
//#define ESP_32

// Network credentials
const char* SSID = "NETWORK-NAME";
const char* PASS = "NETWORK-PASSWORD";

#define LedPin 3
#define LedPWM 204          // Default power, comment line to disable led PWM
#define LedActive HIGH

#define MotorPin 1          // Uncomment to use motor for part rotation
#define MotorPWM 25.5       // Default speed, comment line to disable motor PWM
#define MotorActive HIGH

//#define ButtonPin 2         // Set button pin number and type
//#define ButtonMode INPUT    // External pull-up
//#define ButtonActive LOW    // NC switch

//#define Button1Pin 4
//#define Button1Mode INPUT
//#define Button1Active LOW

//#define Button2Pin 4
//#define Button2Mode INPUT
//#define Button2Active LOW

#include <headers/station.h>

#if defined(ButtonPin) || defined(Button1Pin) || defined(Button2Pin)
    #define BUTTONS
    #include <headers/buttons.h>
#endif

#if defined(ESP_8266) || defined(ESP_32)
    #define WIFI
    #include <headers/server.h>
#endif

#define Config_h