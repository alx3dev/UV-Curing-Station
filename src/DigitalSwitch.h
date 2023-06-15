#ifndef Arduino_h
    #include <Arduino.h>
#endif

#define ACTIVE_HIGH 1
#define ACTIVE_LOW 0

#define AUTO_OFF true


class DigitalSwitch {

    private:
        byte pin;
        byte activeSignal;   // HIGH or LOW

    public:
        bool isON = false;
        byte dutyCycle = 204; // 80%
        bool isPWM = false;

        bool timer;
        unsigned long pause;
        unsigned long triggered = 0UL;

    DigitalSwitch(byte switch_pin, byte switch_on = ACTIVE_HIGH, 
                  bool use_timer = false, int pause_time = 600)
    {
        pin = switch_pin;
        activeSignal = switch_on;

        timer = use_timer;
        pause = pause_time * 1000;

        pinMode(pin, OUTPUT);
        turnOFF();
    }

    void pwm(bool state = true, byte cycle = 204) {
        isPWM = state;
        dutyCycle = cycle;
        if (isON && isPWM) { pulse(cycle); }
    }

    void pulse(byte cycle) {
        analogWrite(pin, cycle);
    }
    
    void turnON() {
        isPWM ? pulse(dutyCycle) : digitalWrite(pin, activeSignal);
        triggered = millis();
        isON = true;
    }

    void turnOFF() {
        digitalWrite(pin, !activeSignal);
        isON = false;
    }
  
    void trigger() {
        isON ? turnOFF() : turnON();
    }

    void autoOFF() {
        if (timer && isON) {
            if (millis() - triggered > pause) { turnOFF(); }
        }
    }
  };
