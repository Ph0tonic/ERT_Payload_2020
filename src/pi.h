#pragma once

#include "packet.h"

enum PiOrder {
    START_RECCORD=1,
    END_RECCORD=2,
    GET_IMAGE_BYTES=3
};

const int PIN_PI_OFF = 14;

void setupPi();
void shutdownPi();
void wakeUpPi();
void sendPiOrder(PiOrder order, String param);
Packet readPiData();
byte* getImage();

void readMessage();
