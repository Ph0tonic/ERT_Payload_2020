
#include <Arduino.h>

#include "pi.h"

void setupPi()
{
    pinMode(PIN_PI_OFF, OUTPUT);
    Serial1.begin(9600);
}

void shutdownPi()
{
    digitalWrite(PIN_PI_OFF, HIGH);
}

void wakeUpPi()
{
    digitalWrite(PIN_PI_OFF, HIGH);
}

void readData()
{
    if(Serial1.available()){
        int size = Serial1.read();
        // TODO: Read data
        String data = Serial.read();
    }
}

void sendData(String data)
{
    Serial1.println(data);
    Serial1.flush();
}
