# UV Curing Station - Under Development

## About

Firmware for UV curing station for resin 3D printers. Intended to run on ESP microcontrollers (because of WiFi), but you can also use other boards supported by Arduino library (buttons are not yet implemented).  

For ESP users, there's an [GUI app under development](https://github.com/alx3dev/Wireless-UV-Station).

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