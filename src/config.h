// ** Configuration for UV Station ** //
#define Config_h

// Define board chip 
#define ESP_8266
//#define ESP_32


#define WIFI_MODE WIFI_STA      // WiFi mode, station or access point

const char* STA_SSID = "ssid";  // Local network name
const char* STA_PASS = "pass";  // Local network password

const char* AP_SSID = "";       // ESP Access Point name
const char* AP_PASS = "";       // ESP Access Point password

#define LedPin 3
#define LedPWM 204              // Default power, comment line to disable led PWM
#define LedActive HIGH

#define MotorPin 1              // Uncomment to use motor for part rotation
#define MotorPWM 25.5           // Default speed, comment line to disable motor PWM
#define MotorActive HIGH

//#define ButtonPin 2           // Set button pin number and type
//#define ButtonMode INPUT      // External pull-up
//#define ButtonActive LOW      // NC switch

//#define Button1Pin 4
//#define Button1Mode INPUT
//#define Button1Active LOW

//#define Button2Pin 4
//#define Button2Mode INPUT
//#define Button2Active LOW

#if defined(ESP_8266) || defined(ESP_32)
    #define WIFI
#endif

#if defined(ButtonPin) || defined(Button1Pin) || defined(Button2Pin)
    #define BUTTONS
#endif