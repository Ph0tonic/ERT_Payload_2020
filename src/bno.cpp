#include "bno.h"

static bool setupFail = false;

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

//#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
sensors_event_t event;

void setupBno()
{
    Serial.println("BNO config");
    if (!bno.begin())
    {
        setupFail = true;
        Serial.println("Failed to initialize BNO055! Is the sensor connected?");
    }
    else
    {
        Serial.println("BNO55 initialized succesfully");
    }

    // delay(1000);

    /* Use external crystal for better accuracy */
    bno.setExtCrystalUse(true);
}

void sampleBNO()
{
    bno.getEvent(&event);
}

// sensors_event_t getSampleData()
// {
//     return event;
// }

float getAcceleration()
{
    //TODO: Check if this acceleration correspond to the wanted one
    // return (float)bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL).magnitude;
    return (float)event.acceleration.heading;
}

// float getRoll()
// {
//     return (float)event.orientation.x;
// }

// float getPitch()
// {
//     return (float)event.orientation.y;
// }

// float getHeadings()
// {
//     return (float)event.orientation.z;
// }


void displaySensorDetails()
{
    sensor_t sensor;
    bno.getSensor(&sensor);
    Serial.println("------------------------------------");
    Serial.print("Sensor:       ");
    Serial.println(sensor.name);
    Serial.print("Driver Ver:   ");
    Serial.println(sensor.version);
    Serial.print("Unique ID:    ");
    Serial.println(sensor.sensor_id);
    Serial.print("Max Value:    ");
    Serial.print(sensor.max_value);
    Serial.println(" xxx");
    Serial.print("Min Value:    ");
    Serial.print(sensor.min_value);
    Serial.println(" xxx");
    Serial.print("Resolution:   ");
    Serial.print(sensor.resolution);
    Serial.println(" xxx");
    Serial.println("------------------------------------");
    Serial.println("");
    delay(500);
}

void displaySensorEvents()
{
    /* Get a new sensor event */
    sensors_event_t event;
    bno.getEvent(&event);

    /* Board layout:
         +----------+
         |         *| RST   PITCH  ROLL  HEADING
     ADR |*        *| SCL
     INT |*        *| SDA     ^            /->
     PS1 |*        *| GND     |            |
     PS0 |*        *| 3VO     Y    Z-->    \-X
         |         *| VIN
         +----------+
    */

    /* The processing sketch expects data as roll, pitch, heading */
    Serial.print(F("Orientation: "));
    Serial.print((float)event.orientation.x);
    Serial.print(F(" "));
    Serial.print((float)event.orientation.y);
    Serial.print(F(" "));
    Serial.print((float)event.orientation.z);
    Serial.println(F(""));
    
    /* Also send calibration data for each sensor. */
    uint8_t sys, gyro, accel, mag = 0;
    bno.getCalibration(&sys, &gyro, &accel, &mag);
    Serial.print(F("Calibration: "));
    Serial.print(sys, DEC);
    Serial.print(F(" "));
    Serial.print(gyro, DEC);
    Serial.print(F(" "));
    Serial.print(accel, DEC);
    Serial.print(F(" "));
    Serial.println(mag, DEC);

    //delay(BNO055_SAMPLERATE_DELAY_MS);
}
