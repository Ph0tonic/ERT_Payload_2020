#pragma once

#include <Arduino.h>

static const uint8_t HEADER[] = {
    0x7E,                                           // First bit signal
    0x00, 0x10,                                     // size
    0x10,                                           // Frame type // Transmit Request frame - 0x10
    0x00,                                           // Frame ID - Setting it to '0' will disable response frame.
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, // 64 bit dest address // broadcast
    0xff, 0xfe,                                     // 16 bits dest address (0xff fe = broadcast) unknown address
    0x00,                                           // Broadcast radius (0 = max) no hops
    0x43,                                           // Tx options
};

enum OrderEnum
{
    NONE,
    GET_STATE = 1,
    SHUTDOWN = 2,
    WAKE = 3,
    INJECT = 4,
    BYPASS_INJECT = 5,
    REC = 6,
    GET_IMAGE = 7,
    ABORT = 8
};

struct Packet
{
    int size;
    uint8_t *data;
};

static const int HEADER_SIZE = sizeof(HEADER) / sizeof(*HEADER);
static const int CRC_SIZE = 1;
static const int CRC_INDEX_START = 3;

Packet createPacket(uint8_t *data, int dataSize);

Packet createEmptyPacket();
Packet createStatePacket(uint8_t state);
Packet createGpsPacket(uint8_t sats_num, float hdop, float latitude, float longitude, float altitude);
Packet createBMEPacket(float temperature, float pressure, float humidity, float altitude);
Packet createBNOPacket(int8_t temperature, float* orientation, float* acceleration);

OrderEnum parseMessage(Packet packet);

// Tools

/**
 * Write the header inside packet
 * Requires packet size at least the size of HEADER
 */
void write(uint8_t *data, float value);

void writeHeader(uint8_t *packet, uint16_t size);
void writeData(uint8_t *packet, uint8_t *data, int dataSize);
void writeCrc(uint8_t *packet, int packetSize);
