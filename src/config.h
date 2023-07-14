#ifndef UVS_CONFIG_H
#define UVS_CONFIG_H

/*
    UV Station Configuration
*/

// Define board chip 
#define BOARD_ESP8266
//#define BOARD_ESP32


// WiFi mode - station, access point or both (WIFI_STA, WIFI_AP, WIFI_AP_STA)
#define UVS_WIFI_MODE   WIFI_STA

const char* STA_SSID =  "ssid";     // Local network name
const char* STA_PASS =  "pass"; // Local network password

const char* AP_SSID =   "";     // ESP Access Point name
const char* AP_PASS =   "";     // ESP Access Point password

#define LedPin      3
#define LedActive   HIGH
#define LedPWM      204.f       // Default power, comment line to disable led PWM

// Uncomment to use motor for part rotation
#define MotorPin    1
#define MotorActive HIGH
#define MotorPWM    25.f        // Default speed, comment line to disable motor PWM

// PWM Configuration (same channel for light and motor).  
// They share frequency, but not duty cycle

#define UVS_PWM_CHANNEL     0  
#define UVS_PWM_RESOLUTION  8       // 0-255
#define UVS_PWM_FREQUENCY   5000    // 5kHz

//#define Button0Pin    2           // Set button pin number and type
//#define Button0Mode   INPUT       // External pull-up
//#define Button0Active LOW         // NC switch

//#define Button1Pin    4
//#define Button1Mode   INPUT
//#define Button1Active LOW

//#define Button2Pin    4
//#define Button2Mode   INPUT
//#define Button2Active LOW


#if defined(BOARD_ESP8266) || defined(BOARD_ESP32)
    #define UVS_WIFI
#endif

#if defined(Button0Pin) || defined(Button1Pin) || defined(Button2Pin)
    #define UVS_BUTTONS
#endif

#endif