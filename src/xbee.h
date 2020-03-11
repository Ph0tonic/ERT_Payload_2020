#pragma once

#include <Arduino.h>
#include "packet.h"

void setupXbee();
void sendXbee(Packet packet);
OrderEnum readXbee()
