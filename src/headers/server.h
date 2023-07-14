#if defined(UVS_WIFI) && !defined(UVS_SERVER_H)
#define UVS_SERVER_H

#ifdef BOARD_ESP8266
  #include <ESP8266WiFi.h>
  #include <WiFiClient.h>
  #include <ESP8266WebServer.h>
  #include <ESP8266mDNS.h>
#endif

#ifdef BOARD_ESP32
  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <ESPmDNS.h>
  #include <WebServer.h>
#endif

namespace UVS {

#ifdef BOARD_ESP8266
  ESP8266WebServer server(80);
#endif

#ifdef BOARD_ESP32
  WebServer server(80);
#endif

void updateSettingsFromRequest()
{
    String opt;

    for (int x = 0; x < server.args(); x++) {
        opt = server.argName(x);
        opt.toLowerCase();

        if (opt == "cycle")
        {
            cycleTimer(server.arg(x).toInt());
        }
        else if (opt == "power")
        {
            Led.pwm(server.arg(x).toFloat());
        }
        else if (opt == "speed")
        {
            #if defined(MotorPin) && defined(MotorPWM)
              Motor.pwm(server.arg(x).toFloat());
            #endif
        }
    }
}

void handleRoot()
{
    server.send(200, "text/plain", "Wireless UV Station");
}

void handleStart()
{
    updateSettingsFromRequest();
    On();
    server.send(200, "text/plain", "Curing cycle started");
}

void handleUpdate()
{
    updateSettingsFromRequest();
    server.send(200, "text/plain", "Controls Updated");
}

void handleStop()
{
    Off();
    server.send(200, "text/plain", "Cycle stopped");
}

void handleTimerDisable()
{
    cycleTimer(false);
    server.send(200, "text/plain", "Timer Disabled");
}

void handleTimerEnable()
{
    if (server.argName(0) == "cycle") {
        cycleTimer(server.arg(0).toInt());
    } else {
        cycleTimer();
    }
    server.send(200, "text/plain", "Timer Enabled");
}

void handleNotFound()
{
    server.send(404, "text/plain", "Error 404");
}

// Initialize WiFi and server, handle request/response.
void server_init()
{
    WiFi.mode(UVS_WIFI_MODE);

    switch (UVS_WIFI_MODE) {

    case WIFI_STA:
        WiFi.begin(STA_SSID, STA_PASS);
        while (WiFi.status() != WL_CONNECTED) { delay(100); }

    case WIFI_AP:
        WiFi.softAP(AP_SSID, AP_PASS);

    case WIFI_AP_STA:
        WiFi.softAP(AP_SSID, AP_PASS);
        WiFi.begin(STA_SSID, STA_PASS);
        while (WiFi.status() != WL_CONNECTED) { delay(100); }

    case WIFI_OFF:
        return void(1);
    }

    server.on("/", handleRoot);
    server.on("/start", handleStart);
    server.on("/update", handleUpdate);
    server.on("/stop", handleStop);
    server.on("/timer-disable", handleTimerDisable);
    server.on("/timer-enable", handleTimerEnable);

    server.onNotFound(handleNotFound);  
    server.begin();
}
} // namespace

#endif