#include "xbeeRF.h"

#include <Arduino.h>
#include <XBee.h>

//NewSoftSerial nss(ssRX, ssTX);  // not needed for Teensy
#define serial Serial2 // "nss" prints to Arduino Serial Monitor

// Create an XBee object at the top of your sketch
XBee xbee;
XBeeAddress64 addr64;

void setupXbee()
{
    xbee = XBee();

    // Specify the address of the remote XBee (this is the SH + SL)
    addr64 = XBeeAddress64(0x0013a200, 0x403e0f30);

    // Turn on DIO0 (Pin 20)
    //RemoteAtRequest request = new RemoteAtRequest(addr64, "D0", new int[{XBeePin.Capability.DIGITAL_OUTPUT_HIGH.getValue()});

    Serial.println("XbeeRF config");

    // start serial
    serial.begin(9600); // change to Serial1 for Teensy
    xbee.setSerial(serial);
    // if (!bme.begin(0x77, &Wire))
    // {
    //     Serial.println("Could not find a valid BME280 sensor, check wiring!");
    // }
}

// inline void sendMessage()
// {
//     // Create a TX Request
//     ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));

//     // Send your request
//     xbee.send(zbTx);
// }

/**
 * Order must be a String and and with a "\n"
 */
void send(uint8_t *order, uint8_t length)
{
    // // Create an array for holding the data you want to send.
    // uint8_t *payload = order;
    // int payloadLength = length;

    // //Extend payload and add '\n' at the end if missing
    // uint8_t extendedPayload[length + 1];
    // if (order[payloadLength - 1] != '\n')
    // {
    //     throw new Param
    //     for (int i = 0; i < payloadLength; ++i)
    //     {
    //         extendedPayload[i] = payload[i];
    //     }
    //     extendedPayload[payloadLength++] = '\n';
    //     payload = extendedPayload;
    // }

    // Create a TX Request
    ZBTxRequest zbTx = ZBTxRequest(addr64, order, length);

    // Send your request
    xbee.send(zbTx);
}

void sendXbee(uint8_t *order, uint64_t length)
{
    // // Create an array for holding the data you want to send.
    // uint8_t *payload = order;
    // int payloadLength = length;

    // //Extend payload and add '\n' at the end if missing
    // uint8_t extendedPayload[length + 1];
    // if (order[payloadLength - 1] != '\n')
    // {
    //     throw new Param
    //     for (int i = 0; i < payloadLength; ++i)
    //     {
    //         extendedPayload[i] = payload[i];
    //     }
    //     extendedPayload[payloadLength++] = '\n';
    //     payload = extendedPayload;
    // }

    // Create a TX Request
    ZBTxRequest zbTx = ZBTxRequest(addr64, order, length);

    // Send your request
    xbee.send(zbTx);
}

int readXbee(){
  if (Serial1.available()) {
    return Serial1.read();  // will not be -1
  }
  return -1;
}