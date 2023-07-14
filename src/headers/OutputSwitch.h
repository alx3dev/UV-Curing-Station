#ifndef UVS_OUTPUT_SWITCH_H
#define UVS_OUTPUT_SWITCH_H

namespace UVS {

// Control output switch (Led and Motor in UV Station).  
// PWM with analogWrite/ledcWrite.  
class OutputSwitch {

private:
    const uint8_t pin;
    const uint8_t activeSignal; // HIGH or LOW

    float dutyCycle = 0.0f;     // GUI should care about percents.

    void activate() { digitalWrite(pin, activeSignal); }
    void deactivate() { digitalWrite(pin, !activeSignal); }

public:
    bool PWM = false;       // use pwm, or full ON/OFF?

    OutputSwitch(uint8_t sw_pin, uint8_t sw_active_sig = HIGH) : pin(sw_pin), activeSignal(sw_active_sig)
    {
        pinMode(pin, OUTPUT);    
        off();
    }

    // Set PWM channel, resolution, frequency and duty cycle.
    void pwm_init(uint8_t pwm_ch, uint8_t pwm_res, uint32_t pwm_freq_hz, float pwm_dc)
    {
        #ifdef BOARD_ESP8266
          analogWriteResolution(pwm_res);
          analogWriteFreq(pwm_freq_hz);
        #endif

        #ifdef BOARD_ESP32
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

        #if defined(BOARD_ESP32)
            ledcWrite(pin, duty);
        #else
            analogWrite(pin, duty);
        #endif
    }

    // Call analogWrite only if PWM is enabled.
    void on()
    {
        PWM ? pulse(dutyCycle) : activate();
    }

    void off()
    {
        deactivate();
    }
};
} // namespace

#endif