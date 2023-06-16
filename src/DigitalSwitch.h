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
        float dutyCycle;
        bool isPWM;
        
        bool isON;
        bool timer;

        unsigned long cycle;
        unsigned long triggered = 0UL;

    DigitalSwitch(byte switch_pin, byte switch_on = ACTIVE_HIGH, 
                  bool use_timer = false, int cycle_time = 600)
    {
        pin = switch_pin;
        activeSignal = switch_on;

        isON = false;
        isPWM = false;

        timer = use_timer;
        cycle = cycle_time * 1000;

        pinMode(pin, OUTPUT);
        turnOFF();
    }

    void pwm(bool state = true, float rate = 204) {
        isPWM = state;
        dutyCycle = rate;
        if (isON && isPWM) { pulse(rate); }
    }

    void pulse(float rate) {
        analogWrite(pin, rate);
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
            if (millis() - triggered > cycle) { turnOFF(); }
        }
    }
  };