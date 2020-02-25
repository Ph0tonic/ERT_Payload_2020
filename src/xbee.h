#pragma once

#include <Arduino.h>

void setupXbee();
void sendXbee(uint8_t *order, uint8_t length);
int readXbee();
