# UV Curing Station - Under Development

## About

Firmware for UV curing station for resin 3D printers. Intended to run on ESP microcontrollers (because of WiFi), but you can also use other boards supported by Arduino library. For ESP users, there's an [GUI app under development](https://github.com/alx3dev/Wireless-UV-Station).

## Supported Options

 - Enable WiFi and run server if using Espressif chip,  
 - DC motor for part rotation,  
 - PWM for Led and/or motor (with analogWrite),  
 - Active-low switch for relay if using AC UV light (COB),  
 - Automatic turn-off after cycle is done.

 ## To-Do

  - Support physical buttons,  
  - Temperature and humidity sensor.