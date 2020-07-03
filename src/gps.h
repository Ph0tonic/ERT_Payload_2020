#pragma once

void setupGps();

bool sampleGPS();
bool getLocalisation(float *lat, float *lng, float *alt, int *sat, float *hd);
