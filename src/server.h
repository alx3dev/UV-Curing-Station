#ifdef ESP_8266
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h>
    #include <WiFiClient.h>
    #include <ESP8266mDNS.h>
    
    ESP8266WebServer server(80);
#endif


#ifdef ESP_32
    #include <WiFi.h>
    // TO-DO
#endif


#ifdef WIFI
    String resp;

    void handleRoot() {
        server.send(200, "text/plain", "Wireless UV Station");
    }

    void handleStart() {
        uvsON();

        resp = "UV Cycle Started\n";
        resp += "UV Power: " + Led.dutyCycle*100/255;
        resp += "%\n";

        #ifdef MotorMosfetPin
            resp += "Motor Speed: " + Motor.dutyCycle*100/255;
            resp += "%\n";
        #endif

        if (Led.timer) {
            resp += "Cycle Time: " + Led.pause/1000;
            resp += " sec";
        }

        server.send(200, "text/plain", resp);
    }

    void handleStop() {
        uvsOFF();
        server.send(200, "text/plain", "Cycle stopped");
    }

    void handleTimerDisable() {
        uvs_setTimer(false);
        server.send(200, "text/plain", "Timer Disabled");
    }

    void handleNotFound() {
        server.send(404, "text/plain", "");
    }

    void server_init() {
        WiFi.mode(WIFI_STA);
        WiFi.begin(SSID, PASS);

        server.onNotFound(handleNotFound);
        server.on("/", handleRoot);
        server.on("/start", handleStart);
        server.on("/stop", handleStop);
        server.on("/disable-timer", handleTimerDisable);
        server.begin();
    }
#endif