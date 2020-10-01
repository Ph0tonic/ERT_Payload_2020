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
    uint8_t data[2] = {0xff, 0xfe};
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

Packet createGpsPacket(uint8_t sats_num, float hdop, float latitude, float longitude, float altitude)
{
    int time = millis();

    uint8_t data[26] = {
        4,
        'E',
        'P',
        'F',
        'L',
        time >> 24,
        time >> 16,
        time >> 8,
        time,
        sats_num
    };
    
    write(data + 10, hdop);
    write(data + 14, latitude);
    write(data + 18, longitude);
    write(data + 22, altitude);

    return createPacket(data, 26);
}

Packet createStatePacket(uint8_t state)
{
    uint8_t data[1] = {state};
    return createPacket(data, 1);
}

Packet createTemperaturePacket(float temperature)
{
    int time = millis();
    uint8_t data[13] = {
        1,
        'E',
        'P',
        'F',
        'L',
        time >> 24,
        time >> 16,
        time >> 8,
        time
    };
    
    write(data + 9, temperature);

    return createPacket(data, 13);
}

Packet createBNOPacket(int8_t temperature, float* orientation, float* acceleration)
{
        
    int time = millis();
    uint8_t data[34] = {
        2,
        'E',
        'P',
        'F',
        'L',
        time >> 24,
        time >> 16,
        time >> 8,
        time,
        temperature
    };
    
    write(data + 10, orientation[0]);
    write(data + 14, orientation[1]);
    write(data + 18, orientation[2]);
    write(data + 22, acceleration[0]);
    write(data + 26, acceleration[1]);
    write(data + 30, acceleration[2]);

    return createPacket(data, 34);
}

Packet createBMEPacket(float temperature, float pressure, float humidity, float altitude)
{
    
    int time = millis();
    uint8_t data[25] = {
        3,
        'E',
        'P',
        'F',
        'L',
        time >> 24,
        time >> 16,
        time >> 8,
        time
    };

    write(data + 9, temperature);
    write(data + 13, pressure);
    write(data + 17, humidity);
    write(data + 21, altitude);
    return createPacket(data, 25);
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

    writeHeader(packet.data, packet.size - 4);
    writeData(packet.data, data, dataSize);
    writeCrc(packet.data, packet.size);

    return packet;
}

/**
 * Write the header inside packet
 * Requires packet size atleastr the size of HEADER
 */
void writeHeader(uint8_t *packet, uint16_t size)
{
    for (int i = 0; i < HEADER_SIZE; ++i)
    {
        packet[i] = HEADER[i];
    }
    packet[1] = size >> 8;
    packet[2] = size;
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

void write(uint8_t *data, float value)
{
    uint8_t *array;
    array = reinterpret_cast<uint8_t*>(&value);    
    data[0] = array[3];
    data[1] = array[2];
    data[2] = array[1];
    data[3] = array[0];
}
