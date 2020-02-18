
#include <Arduino.h>

#include "pi.h"

#define serial Serial4

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
    if(serial.available()){
        int size = serial.read();
        // TODO: Read data
        String data = serial.read();
    }
}

void sendPiOrder(PiOrder order)
{
    //serial.write(12);
    serial.println("Test");
    serial.flush();
}

void sendData(String data)
{
    serial.println(data);
    serial.flush();
}
