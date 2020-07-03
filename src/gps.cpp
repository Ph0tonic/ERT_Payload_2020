#include "bme.h"

#include <TinyGPS++.h>

#define gpsSerial Serial1

TinyGPSPlus gps;

float latitude = 0;
float longitude = 0;
float altitude = 0;
float hdop = 0;
int nb_sat = 0;
bool data = false;

void setupGps()
{
    gpsSerial.begin(9600);
}

bool sampleGPS()
{
    while (gpsSerial.available() > 0)
    {
        char c = gpsSerial.read();
        if (gps.encode(c))
        {
            data = true;
        }
    }

    if (data)
    {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
        altitude = gps.altitude.meters();
        nb_sat = gps.satellites.value();
        hdop = gps.hdop.value();
    }
    return data;
}

bool getLocalisation(float *lat, float *lng, float *alt, int *sat, float *hd)
{
    if (data)
    {
        *lat = latitude;
        *lng = longitude;
        *alt = altitude;
        *sat = nb_sat;
        *hd = hdop;
    }
    return data;
}
