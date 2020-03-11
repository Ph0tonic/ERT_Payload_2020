#include "xbee.h"

#include <Arduino.h>
#include <XBee.h>

#define serial Serial5

void setupXbee()
{
    serial.println("Xbee config");

    // start serial
    serial.begin(115200); // change to Serial1 for Teensy
}

/**
 * Order must be a String and and with a "\n"
 */
void sendXbee(Packet packet)
{
    // uint8_t command[] = {0x7E, //First bit signal
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
    serial.write(packet.data, packet.size);

    // for(int i=0;i<sizeof(command);++i) {
    //     serial.write(command[i]);
    // }

    // /** XBEE START PACKET **/
    // int mallocSize = 29;
    // uint8_t *data = new uint8_t[mallocSize]();
    // data[0] = 0x7E;

    // //Size
    // uint16_t size = 25;
    // data[1] = size >> 8;
    // data[2] = size;

    // /** XBEE OPTIONS **/
    // data[3] = 0x10;
    // data[4] = 0x00;
    // //Broadcast address
    // data[5] = 0x00;
    // data[6] = 0x00;
    // data[7] = 0x00;
    // data[8] = 0x00;
    // data[9] = 0x00;
    // data[10] = 0x00;
    // data[11] = 0xff;
    // data[12] = 0xff;
    // //Dest address
    // data[13] = 0xff;
    // data[14] = 0xfe;
    // //broadcast radius
    // data[15] = 0x00;
    // //Tx options
    // data[16] = 0x43;

    // /** HEADER **/
    // //Datagram ID
    // data[17] = 0x12;
    // //Prefix
    // data[18] = 'E';
    // data[19] = 'P';
    // data[20] = 'F';
    // data[21] = 'L';
    // //TimeStamp
    // uint32_t date = 12;
    // data[22] = date >> 24;
    // data[23] = date >> 16;
    // data[24] = date >> 8;
    // data[25] = date;
    // //Ack
    // data[26] = 1;

    // /** REAL DATA **/
    // data[27] = 1;

    // uint8_t crc = 0x00;
    // for (int i = 3; i < 28; ++i)
    // {
    //     crc += data[i];
    // }

    // /** CRC **/
    // data[28] = crc;

    // for(int i=0;i<29;++i) {
    //     serial.write(data[i]);
    // }
}

OrderEnum readXbee()
{
    if (serial.available())
    {
        uint8_t info[3];
        serial.readBytes(info, 3);
        uint16_t size = (info[1] << 8)| info[2];
        uint8_t data[size];
        serial.readBytes(data, size + 1);
        return (OrderEnum)data[HEADER_SIZE-3+1];
    }
    return NONE;
}

/* Packet
delimiter 1B
Length 2B
Packet Header
Real Data
Checksum 1B
*/