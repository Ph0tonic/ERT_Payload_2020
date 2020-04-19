
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

Packet readPiData()
{
    Packet packet{
        .size = 0,
        .data = nullptr
    };
    if(serial.available())
    {
        int8_t b1 = serial.read();
        int8_t b2 = serial.read();
        packet.size = b2 << 8 | b1;
    } else {
        return packet;
    }
    Serial.print("Packet of size ");
    Serial.print(packet.size);
    Serial.println("received and content is :");

    packet.data = new uint8_t[packet.size];
    int i = 0;
    while(i<packet.size) {
        if(serial.available()){
            i += serial.readBytes(packet.data + i, packet.size-i);
            Serial.println(i);
        } else {
            //delay(20);
        }
    }
    i = 0;
    while(i<packet.size) {
        Serial.println(packet.data[i]);
        i++;
    }
    return packet;
}

void sendPiOrder(PiOrder order, String param)
{
    switch (order)
    {
    case PiOrder::GET_IMAGE_BYTES:
        serial.println((int)order);
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
