#ifndef UVS_STATION_H
#define UVS_STATION_H

#include <headers/OutputSwitch.h>

namespace UVS {
    
OutputSwitch Led( LedPin, LedActive );

#ifdef MotorPin
OutputSwitch Motor( MotorPin, MotorActive );
#endif

bool isActive = false;
bool cycle_timer = true;

uint32_t cycle_ms = 600000U;
uint32_t triggered_ms = 0U;

// All settings goes here, to be called in setup()
void init()
{
    #ifdef LedPWM
      Led.pwm_init(UVS_PWM_CHANNEL, UVS_PWM_RESOLUTION, UVS_PWM_FREQUENCY, LedPWM);
    #endif

    #if defined(MotorPin) && defined(MotorPWM)
      Motor.pwm_init(UVS_PWM_CHANNEL, UVS_PWM_RESOLUTION, UVS_PWM_FREQUENCY, MotorPWM);
    #endif
}

// Turn station ON
void On()
{
    isActive = true;
    Led.on();

    #ifdef MotorPin
      Motor.on();
    #endif

    triggered_ms = millis();
}

// Turn station OFF
void Off()
{
    isActive = false;
    Led.off();

    #ifdef MotorPin
      Motor.off();
    #endif
}

// Enable/Disable timer.
// Set cycle time in seconds.
// Get current settings.
uint32_t cycleTimer(bool status = true, uint16_t sec = 0)
{
    cycle_timer = status;
    if (sec > 0) {
        cycle_ms = sec * 1000;
    }

    return cycle_ms;
}

uint32_t elapsed()
{
    return isActive ? uint32_t(millis() - triggered_ms) : 0;
}

bool curingCycle()
{
    if (cycle_timer && (elapsed() > cycle_ms)) {
        Off();
        return true;
    }
    return false;
}
} // namespace

#endif