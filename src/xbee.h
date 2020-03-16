#pragma once

#include <Arduino.h>
#include "packet.h"

namespace xbee 
{    
    enum MessageType
    {
        Image_packet,
        GSP_Packet,
        State_Packet
    };
}

void setupXbee();
void sendXbee(Packet packet);
OrderEnum readXbee();
