#pragma once

#include <Arduino.h>

void setupBno();

void displaySensorDetails();
void displaySensorEvents();

void sampleBNO();

int8_t getBNOTemperatureC();
void getOrientation(float* data);
void getAcceleration(float* data);
