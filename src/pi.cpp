
#include <Arduino.h>

#include "pi.h"

void setupPi()
{
    pinMode(PIN_PI_OFF, OUTPUT);
}

void shutdownPi()
{
    digitalWrite(PIN_PI_OFF, HIGH);
}

void wakeUpPi()
{
    digitalWrite(PIN_PI_OFF, HIGH);
}
