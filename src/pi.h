#pragma once

const int PIN_PI_OFF = 14;

enum PiOrder {
    START_RECCORD=1,
    END_RECCORD=2,
    CMD_LINE=3,
};

void setupPi();
void shutdownPi();
void wakeUpPi();
void sendPiOrder(PiOrder order, String param);
byte* getImage();

void readMessage();
