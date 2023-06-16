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
    void handleRoot() {
        server.send(200, "text/plain", "Wireless UV Station");
    }

    void handleStart() {
        server.on("/start", []() {
            String arg;
            
            for (int x = 0; x < server.args(); x++) {
                arg = server.arg(x);

                if (arg == "cycle")
                {
                    Led.cycle = arg.toInt();
                }
                else if (arg == "power")
                {
                    Led.pwm(arg.toFloat());
                }
                else if (arg == "speed")
                {
                    #ifdef MotorPin
                        Motor.pwm(arg.toInt());
                    #endif
                }
            }
            uvsON();
            server.send(200, "text/plain", "Curing cycle started.");
        });
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