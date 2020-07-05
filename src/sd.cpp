#include <Arduino.h>

#include "sd.h"

SdFatSdio sd;
File file;

char csvFileName[] = "log_0000.csv";

#define MaxCount 1000000

#define BASE_NAME_SIZE 4
#define NB_NUMBER_FILE 4

void setupLogging()
{
    if (!sd.begin())
    {
        sd.initErrorHalt();
    }
    generateFileName();
}

void generateFileName()
{
    while (sd.exists(csvFileName))
    {
        if (csvFileName[BASE_NAME_SIZE + NB_NUMBER_FILE - 1] != '9')
        {
            csvFileName[BASE_NAME_SIZE + NB_NUMBER_FILE - 1]++;
        }
        else
        {
            if (csvFileName[BASE_NAME_SIZE + NB_NUMBER_FILE - 2] != '9')
            {
                csvFileName[BASE_NAME_SIZE + NB_NUMBER_FILE - 2]++;
            }
            else
            {
                if (csvFileName[BASE_NAME_SIZE + NB_NUMBER_FILE - 3] != '9')
                {
                    csvFileName[BASE_NAME_SIZE + NB_NUMBER_FILE - 3]++;
                }
                else
                {
                    csvFileName[BASE_NAME_SIZE + NB_NUMBER_FILE - 3] = '0';
                    if (csvFileName[BASE_NAME_SIZE + NB_NUMBER_FILE - 4] == '9')
                    {
                        // Last trial to make it work, we increment the characters
                        csvFileName[0]++;
                        // throw new exception("Can't create file name");
                    }
                    csvFileName[BASE_NAME_SIZE + NB_NUMBER_FILE - 4]++;
                }
                csvFileName[BASE_NAME_SIZE + NB_NUMBER_FILE - 2] = '0';
                csvFileName[BASE_NAME_SIZE + 1]++;
            }
            csvFileName[BASE_NAME_SIZE + NB_NUMBER_FILE - 1] = '0';
            csvFileName[BASE_NAME_SIZE + 2]++;
        }
    }

    Serial.print(F("File renamed: "));
    Serial.println(csvFileName);
}

void logGPS(uint32_t timestamp, float altitude, float latitude, float longitude)
{
    char s[50]; // 4 + (5+1+3) + 1 + (1+2+1+8) + 1 + (1+3+1+8) + 1 = 41
    snprintf_P(s, sizeof(s), PSTR("GPS;%.3f;%.8f;%.8f"), altitude, latitude, longitude);
    log(timestamp, s);
}

void logBNO(uint32_t timestamp, int8_t temperature, float *orientation, float *acceleration)
{
    char s[70]; // 4 + (1+5) + 1 + 3*(1+4+1+2) + 1 + 3*(1+4+1+2) = 60
    snprintf_P(s, sizeof(s), PSTR("BNO;%d;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f"), temperature, orientation[0], orientation[1], orientation[2], acceleration[0], acceleration[1], acceleration[2]);
    log(timestamp, s);
}

void logBME(uint32_t timestamp, float temperature, float pressure, float humidity, float approxAltitude)
{
    char s[50]; // 4 + (1+3+1+3) + 1 + (7+1+3) + 1 + (3+1+3) + 1 + (5+1+3) + 1 = 43
    snprintf_P(s, sizeof(s), PSTR("BME;%.3f;%.3f;%.3f;%.3f"), temperature, pressure, humidity, approxAltitude);
    log(timestamp, s);
}

void log(uint32_t timestamp, char *data)
{
    // following is for logging
    static uint32_t count = 0;

    if (!count)
    {
        generateFileName();
        if (!file.open(csvFileName, O_RDWR | O_CREAT))
        {
            sd.errorHalt("open failed");
        }
        count = 1;
    }

    if (count > 0)
    {
        // write to file
        file.print(timestamp);
        file.print(';');
        file.print(data);
        file.println();

        file.flush();

        count++;
        if (count > MaxCount)
            count = 0;
    }
    //
    if (!count)
    {
        // close file
        file.close();
    }
}