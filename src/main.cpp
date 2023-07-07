#ifndef Arduino_h
    #include <Arduino.h>
#endif

#ifndef Config_h
    #include <config.h>
#endif

void setup()
{
    UVS::init();
}

void loop()
{
    #ifdef WIFI
        server.handleClient();
    #endif

    UVS::autoOFF();
}