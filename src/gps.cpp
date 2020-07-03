#include "bme.h"

static bool setupFail = false;

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h> // TODO Change

void setupGps()
{
    // TODO
}

void getLocalisation(float *latitude, float *longitude, float *altitude, int *nb_sat)
{
    // TODO
    *latitude = 0;
    *longitude = 0;
    *altitude = 0;
    *nb_sat = 0;
}
