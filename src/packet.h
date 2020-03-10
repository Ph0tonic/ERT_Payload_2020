
#include <Arduino.h>

static const uint8_t HEADER[] = {
    0x7E,                                           //First bit signal
    0x00, 0x10,                                     // length
    0x10,                                           // Frame type // Transmit Request frame - 0x10
    0x00,                                           // Frame ID - Setting it to '0' will disable response frame.
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, // 64 bit dest address // broadcast
    0xff, 0xfe,                                     // 16 bits dest address (0xff fe = broadcast) unknown address
    0x00,                                           // Broadcast radius (0 = max) no hops
    0x43,                                           // Tx options
};

static const int HEADER_SIZE = sizeof(HEADER) / sizeof(*HEADER);
static const int CRC_SIZE = 1;

static const int CRC_INDEX_START = 3;


/**
 * Write the header inside packet
 * Requires packet size atleastr the size of HEADER
 */
void writeHeader(uint8_t *packet);
void writeData(uint8_t* packet, uint8_t* data, int dataSize);
void writeCrc(uint8_t* packet, int packetSize);

uint8_t* createPacket(int* finalPacketSize, uint8_t* data, int dataSize);

uint8_t* createEmptyPacket(int* length)
{
  uint8_t data[] = {0xff, 0xfe};
  uint8_t* packet = createPacket(length, data, 2);

  uint8_t crcPrecalculated = 0xb4;
  //4d
  if (packet[(*length) - 1] != crcPrecalculated){
    Serial.print("Error in CRC calculator, expected ");
    Serial.print(crcPrecalculated);
    Serial.print(", got ");
    Serial.println(packet[(*length) - 1]);
  }

  return packet;
}

uint8_t* createGpsPacket(int *length, uint8_t sats_num, float latitude, float longitude, float altitude)
{
  //TODO: GPS Packet
  Serial.println("GPS Packet not implemented yet !");
}

uint8_t* createStatePacket(int *length, uint8_t state)
{
  Serial.println("State Packet not implemented yet !");
  
  uint8_t data[1] = {state};
  return createPacket(length, data, 1);
}

uint8_t* createTemperaturePacket(int *length, float temperature)
{
  Serial.println("State Packet not implemented yet !");
  uint8_t data[4] = {
    (uint32_t)temperature,
    (uint32_t)temperature>>8,
    (uint32_t)temperature>>16,
    (uint32_t)temperature>>24
  };
  return createPacket(length, data, 1);
}

uint8_t* createImagePacket(int *length)
{
  Serial.println("Image Packet not implemented yet !");
}

/* TOOLS */

uint8_t* createPacket(int* finalPacketSize, uint8_t* data, int dataSize)
{
  *finalPacketSize = HEADER_SIZE + dataSize + CRC_SIZE;
  Serial.print("Final Packet Size : ");
  Serial.println(*finalPacketSize);
  uint8_t* packet = new uint8_t[*finalPacketSize];

  writeHeader(packet);
  writeData(packet, data, dataSize);
  writeCrc(packet, *finalPacketSize);

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

void writeData(uint8_t* packet, uint8_t* data, int dataSize)
{
  for (int i = 0; i < dataSize; ++i)
  {
    packet[HEADER_SIZE + i] = data[i];
  }
}

void writeCrc(uint8_t* packet, int packetSize)
{
  uint8_t crc = 0xff;
  for (int i = CRC_INDEX_START; i < packetSize - 1; ++i)
  {
    crc -= packet[i];
  }

  /** CRC **/
  packet[packetSize - 1] = crc;
}