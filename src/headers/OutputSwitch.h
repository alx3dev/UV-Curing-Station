#ifndef Arduino_h
    #include <Arduino.h>
#endif

#define ACTIVE_HIGH 1
#define ACTIVE_LOW 0

#define AUTO_OFF true

// Wrap all the methods needed for output switch into a single class.
// Support PWM (with analogWrite), and timer for automatic turn-off.
class OutputSwitch {

    private:
        byte pin;
        byte activeSignal;   // HIGH or LOW

    public:
        // firmware should use a real values, GUI should care about percents.
        float dutyCycle;

        bool isON;  // track swtich state
        bool isPWM; // use pwm, or full ON/OFF?
        bool timer; // automatic turn-off?

        unsigned long cycle;  // how long to keep switch ON?
        unsigned long triggered = 0UL;  // keep track of switch-on time

    // Initialize given pin as output, driven by active-high or active-low sig.
    // Enable auto-off timer and cycle time in seconds.
    //
    OutputSwitch(byte switch_pin, byte switch_on = ACTIVE_HIGH, 
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

    // Enable/disable switch PWM, and set duty cycle value.
    // Activate pulses only if switch state is already ON.
    void pwm(bool state = true, float rate = 204) {
        isPWM = state;
        dutyCycle = rate;
        if (isON && isPWM) { pulse(rate); }
    }

    // Do not check if PWM is enabled.
    // Purpose is to allow pwm while turnON() still go to full power.
    void pulse(float rate) {
        analogWrite(pin, rate);
    }
    
    // Call analogWrite only if PWM is enabled.
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

    bool autoOFF() {
        if (timer && isON) {
            if (millis() - triggered > cycle) { turnOFF(); }
            return true;
        }
        return false;
    }
  };