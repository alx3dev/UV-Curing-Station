#include <DigitalSwitch.h>

DigitalSwitch Led( LedMosfetPin, OUTPUT, ACTIVE_HIGH, AUTO_OFF, 600 );
DigitalSwitch Motor( MotorMosfetPin );

void uvsON() {
    Led.turnON();
    Motor.turnON();
}

void uvsOFF() {
    Motor.turnOFF();
    Led.turnOFF();
}

void uvs_autoOFF() {
    Led.autoOFF();
}

void uvs_setTimer(bool count = true, int sec = 0) {
    Led.timer = count;
    if (sec > 0) {
        Led.pause = sec * 1000;
    }
}