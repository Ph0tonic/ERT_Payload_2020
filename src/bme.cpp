#include "bme.h"

static bool setupFail = false;

#include <Wire.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void displayBmeValues()
{
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}

void setupBme()
{
    Serial.println("Bme config");

    if (!bme.begin(0x77, &Wire))
    {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
    }
}

float getTemperatureC()
{
    return bme.readTemperature();
}

float getPressureP()
{
    return bme.readPressure();
}

float getAltitudeM()
{
    return bme.readAltitude(SEALEVELPRESSURE_HPA);
}

float getHumidity()
{
    return bme.readHumidity();
}