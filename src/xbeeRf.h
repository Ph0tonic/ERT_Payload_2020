#pragma once

#include <Arduino.h>

#define HOST_ADDRESS 0x0003

void setupXbee();
void sendXbee(uint8_t *order, uint8_t length);
int readXbee();

// enum Direction {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_NONE};
// enum WMessageType {FOOT_STEP, HAND_GESTURE};

// typedef struct WMessage {
//     WMessageType type;
//     Direction direction;
// } WMessage_t;

// class WirelessModule {
// public:
//     WirelessModule(PinName tx, PinName rx, WMessageType type) :
//         uart(tx, rx), xbee(uart),
//         tx16req(HOST_ADDRESS, (uint8_t *) &message, sizeof(message))
//     {
//         uart.baud(9600);
//         message.type = type;
//     }

//     int sendDirection(Direction dir) {
//         message.direction = dir;
//         xbee.send(tx16req);
//         return 0;
//     }
// private:
//     RawSerial uart;
//     XBee xbee;
//     WMessage_t message;
//     Tx16Request tx16req;
// };

// class WirelessHost {
// public:
//     WirelessHost(PinName tx, PinName rx) : uart(tx, rx), xbee(uart) {}

//     int waitForMessage(WMessage_t *store) {
//         xbee.readPacket(5000);

//         if (xbee.getResponse().isError()) {
//             // API error
//             return -99;
//         }

//         if (xbee.getResponse().isAvailable()) {
//             if (xbee.getResponse().getApiId() != RX_16_RESPONSE) {
//                 // Unexpected API message
//                 return -5;
//             }

//             // Retrieve response
//             xbee.getResponse().getRx16Response(rx16resp);

//             // Validate packet length
//             if (rx16resp.getDataLength() == sizeof(WMessage_t)) {
//                 // Store the payload
//                 memcpy(store, rx16resp.getData(), sizeof(WMessage_t));
//                 return 0;
//             } else {
//                 // Unexpected payload format
//                 return -10;
//             }
//         } else {
//             // No Response
//             return -1;
//         }
//     }

// private:
//     RawSerial uart;
//     XBee xbee;
//     Rx16Response rx16resp;
// };

