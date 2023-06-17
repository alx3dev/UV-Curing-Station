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


// Handle requests only if Espressif boards are used
#ifdef WIFI

    // Get and set control values from server request
    void updateSettings() {
        for (int x = 0; x < server.args(); x++) {
            if (server.argName(x) == "cycle")
            {
                Led.cycle = server.arg(x).toInt();
            }
            else if (server.argName(x) == "power")
            {
                Led.pwm(server.arg(x).toFloat());
            }
            else if (server.argName(x) == "speed")
            {
                #ifdef MotorPin
                    Motor.pwm(server.arg(x).toInt());
                #endif
            }
        }
    }

    void handleRoot() {
        server.send(200, "text/plain", "Wireless UV Station");
    }

    void handleStart() {
        updateSettings();
        uvsON();
        server.send(200, "text/plain", "Curing cycle started");
    }

    void handleUpdate() {
        updateSettings();
        server.send(200, "text/plain", "Controls Updated");
    }

    void handleStop() {
        uvsOFF();
        server.send(200, "text/plain", "Cycle stopped");
    }

    void handleTimerDisable() {
        uvs_setTimer(false);
        server.send(200, "text/plain", "Timer Disabled");
    }

    void handleTimerEnable() {
        uvs_setTimer();
        server.send(200, "text/plain", "Timer Enabled");
    }

    void handleNotFound() {
        server.send(404, "text/plain", "");
    }

    // Initialize WiFi and server, handle request/response.
    void server_init() {
        WiFi.mode(WIFI_STA);
        WiFi.begin(SSID, PASS);

        server.on("/", handleRoot);
        server.on("/start", handleStart);
        server.on("/update", handleUpdate);
        server.on("/stop", handleStop);
        server.on("/timer-disable", handleTimerDisable);
        server.on("/timer-enable", handleTimerEnable);

        server.onNotFound(handleNotFound);  
        server.begin();
    }
#endif