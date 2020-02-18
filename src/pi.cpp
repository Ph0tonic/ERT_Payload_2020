
#include <Arduino.h>

#include "pi.h"

#define serial Serial1

void setupPi()
{
    pinMode(PIN_PI_OFF, OUTPUT);
    serial.begin(9600);
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

void sendPiOrder(PiOrder order)
{
    serial.write(order);
    serial.flush();
}

void sendData(String data)
{
    serial.println(data);
    serial.flush();
}
