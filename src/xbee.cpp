#include "xbee.h"

#include <Arduino.h>
#include <XBee.h>

#define serial Serial5

void setupXbee()
{
    Serial.println("Xbee config");

    // start serial
    serial.begin(115200); // change to Serial1 for Teensy
}

/**
 * Order must be a String and and with a "\n"
 */
void sendXbee(Packet packet)
{
    // uint8_t emptyCommand[] = {
    //                     0x7E, //First bit signal
    //                     0x00, 0x10, // length
    //                     0x10,  // Frame type // Transmit Request frame - 0x10
    //                     0x00,  // Frame ID - Setting it to '0' will disable response frame.
    //                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, // 64 bit dest address // broadcast
    //                     0xff, 0xfe, // 16 bits dest address (0xff fe = broadcast) unknown address
    //                     0x00, // Broadcast radius (0 = max) no hops
    //                     0x43,                     0xff, //DATA
    //                     0xfe, //DATA
    //                     0xb4 // CRC
    // };
    Serial.print("Res : ");
    // Serial.println(serial.write(emptyCommand, sizeof(emptyCommand)/sizeof(uint8_t)));
    Serial.println(serial.write(packet.data, packet.size));
}

// OrderEnum readXbee()
// {
//     if (serial.available())
//     {
//         uint8_t info[3];
//         serial.readBytes(info, 3);
//         uint16_t size = (info[1] << 8)| info[2];
//         uint8_t data[size];
//         serial.readBytes(data, size + 1);
//         Serial.println("Received some data :)");
//         return (OrderEnum)data[HEADER_SIZE-3+1];
//     }
//     return NONE;
// }

/* Packet
delimiter 1B
Length 2B
Packet Header
Real Data
Checksum 1B
*/