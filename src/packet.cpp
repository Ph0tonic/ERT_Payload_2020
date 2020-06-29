#include "packet.h"

OrderEnum parseMessage(Packet packet)
{
    if (packet.size != HEADER_SIZE + 4 + CRC_SIZE)
    {
        Serial.write("Received message to small");
        return;
    }

    //TODO: Parse message
    return NONE;
}

Packet createEmptyPacket()
{
    uint8_t data[] = {0xff, 0xfe};
    Packet packet = createPacket(data, 2);

    uint8_t crcPrecalculated = 0xb4;
    if (packet.data[(packet.size) - 1] != crcPrecalculated)
    {
        Serial.print("Error in CRC calculator, expected ");
        Serial.print(crcPrecalculated);
        Serial.print(", got ");
        Serial.println(packet.data[packet.size - 1]);
    }

    return packet;
}

Packet createGpsPacket(uint8_t sats_num, float latitude, float longitude, float altitude)
{
    uint8_t data[13] = {
        sats_num,
        (uint32_t)latitude,
        (uint32_t)latitude >> 8,
        (uint32_t)latitude >> 16,
        (uint32_t)latitude >> 24,
        (uint32_t)longitude,
        (uint32_t)longitude >> 8,
        (uint32_t)longitude >> 16,
        (uint32_t)longitude >> 24,
        (uint32_t)altitude,
        (uint32_t)altitude >> 8,
        (uint32_t)altitude >> 16,
        (uint32_t)altitude >> 24};
    return createPacket(data, 13);
}

Packet createStatePacket(uint8_t state)
{
    uint8_t data[1] = {state};
    return createPacket(data, 1);
}

Packet createTemperaturePacket(float temperature)
{
    uint8_t data[4] = {
        (uint32_t)temperature,
        (uint32_t)temperature >> 8,
        (uint32_t)temperature >> 16,
        (uint32_t)temperature >> 24
    };
    return createPacket(data, 4);
}

Packet createBNOPacket(int8_t temperature, float* orientation, float* acceleration)
{
        uint8_t data[28] = {
        (uint32_t)temperature,
        (uint32_t)temperature >> 8,
        (uint32_t)temperature >> 16,
        (uint32_t)temperature >> 24,
        (uint32_t)orientation[0],
        (uint32_t)orientation[0] >> 8,
        (uint32_t)orientation[0] >> 16,
        (uint32_t)orientation[0] >> 24,
        (uint32_t)orientation[1],
        (uint32_t)orientation[1] >> 8,
        (uint32_t)orientation[1] >> 16,
        (uint32_t)orientation[1] >> 24,
        (uint32_t)orientation[2],
        (uint32_t)orientation[2] >> 8,
        (uint32_t)orientation[2] >> 16,
        (uint32_t)orientation[2] >> 24,
        (uint32_t)acceleration[0],
        (uint32_t)acceleration[0] >> 8,
        (uint32_t)acceleration[0] >> 16,
        (uint32_t)acceleration[0] >> 24,
        (uint32_t)acceleration[1],
        (uint32_t)acceleration[1] >> 8,
        (uint32_t)acceleration[1] >> 16,
        (uint32_t)acceleration[1] >> 24,
        (uint32_t)acceleration[2],
        (uint32_t)acceleration[2] >> 8,
        (uint32_t)acceleration[2] >> 16,
        (uint32_t)acceleration[2] >> 24
    };
    return createPacket(data, 28);
}

Packet createBMEPacket(float temperature, float pressure, float humidity, float altitude)
{
    uint8_t data[16] = {
        (uint32_t)temperature,
        (uint32_t)temperature >> 8,
        (uint32_t)temperature >> 16,
        (uint32_t)temperature >> 24,
        (uint32_t)pressure,
        (uint32_t)pressure >> 8,
        (uint32_t)pressure >> 16,
        (uint32_t)pressure >> 24,
        (uint32_t)humidity,
        (uint32_t)humidity >> 8,
        (uint32_t)humidity >> 16,
        (uint32_t)humidity >> 24,
        (uint32_t)altitude,
        (uint32_t)altitude >> 8,
        (uint32_t)altitude >> 16,
        (uint32_t)altitude >> 24
    };
    return createPacket(data, 16);
}

Packet createImagePacket()
{
    Serial.println("Image Packet not implemented yet !");
}

/* TOOLS */

Packet createPacket(uint8_t *data, int dataSize)
{
    Packet packet;
    packet.size = HEADER_SIZE + dataSize + CRC_SIZE;
    packet.data = new uint8_t[packet.size];
    Serial.print("Final Packet Size : ");
    Serial.println(packet.size);

    writeHeader(packet.data);
    writeData(packet.data, data, dataSize);
    writeCrc(packet.data, packet.size);

    return packet;
}

/**
 * Write the header inside packet
 * Requires packet size atleastr the size of HEADER
 */
void writeHeader(uint8_t *packet)
{
    for (int i = 0; i < HEADER_SIZE; ++i)
    {
        packet[i] = HEADER[i];
    }
}

void writeData(uint8_t *packet, uint8_t *data, int dataSize)
{
    for (int i = 0; i < dataSize; ++i)
    {
        packet[HEADER_SIZE + i] = data[i];
    }
}

void writeCrc(uint8_t *packet, int packetSize)
{
    uint8_t crc = 0xff;
    for (int i = CRC_INDEX_START; i < packetSize - 1; ++i)
    {
        crc -= packet[i];
    }

    packet[packetSize - 1] = crc;
}