#ifndef Arduino_h
  #include <Arduino.h>
#endif

#include <config.h>
#include <headers/station.h>
#include <headers/server.h>
#include <headers/buttons.h>


void setup()
{
    UVS::init();

#ifdef WIFI
    UVS::server_init();
#endif

#ifdef BUTTONS
    UVS::buttons_init();
#endif
}

void loop()
{
#ifdef WIFI
    UVS::server.handleClient();
#endif

    UVS::curingCycle();
}