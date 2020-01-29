#include <Arduino.h>

#include "led.h"

void setupLight()
{
    pinMode(PIN_LED, OUTPUT);
}

void lightOn()
{
    digitalWrite(PIN_LED, HIGH);
}

void lightOff()
{
    digitalWrite(PIN_LED, LOW);
}
