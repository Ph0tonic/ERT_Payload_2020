
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

    //TODO: Wait for confirmation of wakeupp and fully fonctionnal py
    // Choose timeout
}

void getImage(byte** img, size_t* image_size)
{
    serial.println(0); //No params
    serial.flush();

    *image_size = serial.read();
    if(image_size == 0){
        return;
    }
    *img = (byte*)malloc(*image_size);
    serial.readBytes(*img, *image_size);
}

void sendPiOrder(PiOrder order, String param)
{
    switch (order)
    {
    case PiOrder::CMD_LINE:
        serial.print(order);
        serial.print(" ");
        serial.println(param);
        break;
    case PiOrder::END_RECCORD:
    case PiOrder::START_RECCORD:
        serial.println((int)order); //No params
        break;
    default:
        Serial.print("Unknown order");
        Serial.println(order);
        break;
    }
    serial.flush();
}
