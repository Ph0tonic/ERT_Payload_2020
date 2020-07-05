#pragma once

#include "SdFat.h"

void setupLogging();
void generateFileName();

void logGPS(uint32_t timestamp, float altitude, float latitude, float longitude);
void logBNO(uint32_t timestamp, int8_t temperature, float *orientation, float *acceleration);
void logBME(uint32_t timestamp, float temperature, float pressure, float humidity, float approxAltitude);

void log(uint32_t timestamp, char *data);