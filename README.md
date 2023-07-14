# UV Curing Station - Firmware
  
###

# v0.1.0

###
  
Firmware for UV curing station for resin 3D printers.  
Intended to run on ESP microcontrollers because of WiFi, and buttons are not yet implented.  
Other things work as they should, at least on ESP32. Going to test it on ESP8266.
  
##
  
[GUI application](https://github.com/alx3dev/Wireless-UV-Station) is still under development.  
It's written with Fyne (in Golang), and works on Linux, Android, Windows, Mac...

  
## Supported Options

 - Enable WiFi and run server if using Espressif chip,  
 - DC motor for part rotation,  
 - PWM for Led and/or motor (with analogWrite/ledcWrite),  
 - Support active-low switch (if using relay with AC UV-COB),  
 - Automatic turn-off after cycle is done.
 - Easy to add more peripherals.  

## To-Do

 - Support physical buttons (under development),  
 - Temperature and humidity sensor.  
 - 3D printable files  
 - Display support  

## How to compile

 - Open `platformio.ini` and change `devault_envs` to board you are using.  
 - Open `config.h` and edit configuration (board, pins, network credentials).  
