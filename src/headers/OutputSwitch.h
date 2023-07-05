#ifndef Arduino_h
    #include <Arduino.h>
#endif

// Wrap all the methods needed for output switch into a single class.
// Support PWM (with analogWrite), and timer for automatic turn-off.
class OutputSwitch {

    private:
        uint8_t pin;
        uint8_t activeSignal;   // HIGH or LOW

    public:
        // firmware should use a real values, GUI should care about percents.
        float dutyCycle = 0;

        bool isPWM = false; // use pwm, or full ON/OFF?
        bool isTimer = false; // automatic turn-off?
        bool isON  = false; // track swtich state

        uint64_t cycle; // how long to keep switch ON?
        uint64_t triggered = 0; // keep track of switch-on time

    // Initialize given pin as output, driven by active-high or active-low sig.
    // Set cycle time in seconds to enable auto-off (0 mean timer is disabled).
    //
    OutputSwitch(uint8_t sw_pin, uint8_t sw_on = HIGH, uint32_t sw_cycle = 0)
    {
        pin = sw_pin;
        activeSignal = sw_on;

        if (sw_cycle > 0) {
            isTimer = true;
            cycle = sw_cycle * 1000;
        }

        pinMode(pin, OUTPUT);
        off();
    }

    void pulse(float rate) {
        analogWrite(pin, rate);
    }
    
    // Enable/disable switch PWM, and set duty cycle value.
    // Activate pulses only if switch state is already ON.
    void pwm(bool state = true, float rate = 0) {
        isPWM = state;
        dutyCycle = rate;
        if (isON && isPWM) { pulse(rate); }
    }

    // Call analogWrite only if PWM is enabled.
    void on() {
        isPWM ? pulse(dutyCycle) : digitalWrite(pin, activeSignal);
        triggered = millis();
        isON = true;
    }

    void off() {
        digitalWrite(pin, !activeSignal);
        isON = false;
    }
  
    void trigger() {
        isON ? off() : on();
    }

    bool expired() {
        if (isTimer && isON) {
            return millis() - triggered > cycle ? true : false;
        }
        return false;
    }
};

#define OutputSwitch_h