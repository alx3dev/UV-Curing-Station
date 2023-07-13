#ifndef Arduino_h
  #include <Arduino.h>
#endif

#include "./config.h"
#include "./headers/station.h"

#ifdef WIFI
  #include "./headers/server.h"
#endif

#ifdef BUTTONS
  #include "./headers/buttons.h"
#endif


void setup()
{
    UVS::init();

#ifdef WIFI
    UVS::server_init();
#endif
}

void loop()
{
#ifdef WIFI
    UVS::server.handleClient();
#endif

    UVS::curingCycle();
}