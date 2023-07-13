#ifndef Arduino_h
  #include <Arduino.h>
#endif

// Wrap all the methods needed for output switch into a single class.
// Support PWM (with analogWrite/ledcWrite), and timer for automatic turn-off.
class OutputSwitch {

private:
    uint8_t  pin;
    uint8_t  activeSignal;  // HIGH or LOW

    float dutyCycle = 0.0f; // GUI should care about percents.

public:
    bool PWM = false;       // use pwm, or full ON/OFF?

    OutputSwitch(uint8_t sw_pin, uint8_t sw_active_sig = HIGH)
    {
        pin = sw_pin;
        activeSignal = sw_active_sig;
        
        pinMode(pin, OUTPUT);    
        off();
    }

    // Set PWM channel, resolution, frequency and duty cycle.
    void pwm_init(uint8_t pwm_ch = 0, uint8_t pwm_res = 10, uint32_t pwm_freq_hz = 5000, float pwm_dc = 0.f)
    {
    #ifdef ESP8266
        analogWriteResolution(pwm_res);
        analogWriteFreq(pwm_freq_hz);
    #endif

    #ifdef ESP32
        ledcAttachPin(pin, pwm_ch);
        ledcSetup(pwm_ch, pwm_freq_hz, pwm_res);
    #endif

        PWM = true;
        pwm(pwm_dc);
    }

    // Set duty cycle, or get current value with -1.
    float pwm(float dc = -1.f)
    {
        if (dc >= 0.f) { dutyCycle = dc; }
        return dutyCycle;
    }

    // Modulate pulse based on defined board
    void pulse(float duty = -1.f)
    {
        if (duty < 0.f) {
            duty = dutyCycle;
        }

        #if defined(ESP32)
            ledcWrite(pin, duty);
        #else
            analogWrite(pin, duty);
        #endif
    }

    // Call analogWrite only if PWM is enabled.
    void on()
    {
        PWM ? pulse(dutyCycle) : digitalWrite(pin, activeSignal);
    }

    void off()
    {
        digitalWrite(pin, !activeSignal);
    }
};

#define OutputSwitch_h