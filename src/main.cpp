#include <Arduino.h>

#include <config.h>
#include <headers/station.h>
#include <headers/server.h>
#include <headers/buttons.h>


void setup()
{
    UVS::init();

    #ifdef UVS_WIFI
      UVS::server_init();
    #endif
}

void loop()
{
    #ifdef UVS_WIFI
      UVS::server.handleClient();
    #endif

    #ifdef UVS_BUTTONS
      UVS::processButtonPress();
    #endif

    UVS::curingCycle();
}