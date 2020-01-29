#include "buzzer.h"

#include <Arduino.h>

void setupBuzzer()
{
    pinMode(PIN_BUZZER, OUTPUT);
}

void startBuzzing()
{
    digitalWrite(PIN_BUZZER, HIGH);
}

void stopBuzzing()
{
    digitalWrite(PIN_BUZZER, LOW);
}