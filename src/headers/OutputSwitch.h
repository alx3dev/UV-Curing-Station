#ifndef Arduino_h
    #include <Arduino.h>
#endif

// Wrap all the methods needed for output switch into a single class.
// Support PWM (with analogWrite/ledcWrite), and timer for automatic turn-off.
class OutputSwitch {

    private:
        uint8_t  pin;
        uint8_t  activeSignal;      // HIGH or LOW
        uint32_t cycle_ms;          // how long to keep switch ON?
        uint32_t triggered_ms = 0;  // keep track of switch-on time

    public:
        // firmware should use a real values, GUI should care about percents.
        float dutyCycle = 0;

        bool isPWM   = false;   // use pwm, or full ON/OFF?
        bool isTimer = false;   // automatic turn-off?
        bool isON    = false;   // track swtich state


    // Initialize given pin as output, driven by active-high or active-low sig.
    // Set cycle time in seconds to enable auto-off (0 mean timer is disabled).
    //
    OutputSwitch(uint8_t sw_pin, uint8_t sw_on = HIGH, uint16_t sw_cycle = 0)
    {
        pin = sw_pin;
        activeSignal = sw_on;

        if (sw_cycle > 0) {
            isTimer = true;
            setTimer(sw_cycle);
        }
        
        pinMode(pin, OUTPUT);    
        off();
    }

    // Configure PWM, depending on microcontroller
    void pwm_init(uint8_t pwm_ch = 0, uint8_t pwm_res = 10, uint16_t pwm_freq_hz = 5000, float pwm_dc = 0)
    {
        isPWM = true;
        dutyCycle = pwm_dc;

        #ifdef ESP8266
            analogWriteResolution(pwm_res);
            analogWriteFreq(pwm_freq_hz);
        #endif

        #ifdef ESP32
            ledcAttachPin(pin, pwm_ch);
            ledcSetup(pwm_ch, pwm_freq_hz, pwm_res);
        #endif
    }

    // Set value for duty cycle, or update if already ON.
    void power(float duty_cycle)
    {
        dutyCycle = duty_cycle;
        if (isON && isPWM) { pulse(duty_cycle); }
    }

    // Modulate pulse based on defined board
    void pulse(float duty)
    {
        #if defined(ESP32)
            ledcWrite(pin, duty);
        #else
            analogWrite(pin, duty);
        #endif
    }

    // Call analogWrite only if PWM is enabled.
    void on()
    {
        isPWM ? pulse(dutyCycle) : digitalWrite(pin, activeSignal);
        triggered_ms = millis();
        isON = true;
    }

    void off()
    {
        digitalWrite(pin, !activeSignal);
        isON = false;
    }
  
    void trigger()
    {
        isON ? off() : on();
    }

    void setTimer(bool status = true, uint16_t sec = 0)
    {
        isTimer = status;
        if (sec > 0) { cycle_ms = sec * 1000; }
    }

    uint16_t cycleTime() {
        return cycle_ms / 1000;
    }

    uint32_t elapsed() {
        return millis() - triggered_ms;
    }

    bool expired()
    {
        if (isTimer && isON) {
            return elapsed() > cycle_ms ? true : false;
        }
        return false;
    }
};

#define OutputSwitch_h