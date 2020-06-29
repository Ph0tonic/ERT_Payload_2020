#include <Arduino.h>

// #include "pi.h"
#include "buzzer.h"
#include "led.h"
#include "bno.h"
#include "bme.h"
#include "packet.h"
#include "xbee.h"
#include "sd.h"

#define DEBUG true

// To be determined
#define GPS_LOG_MS 200
#define GPS_XBEE_MS 200

// https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout
#define BME_LOG_MS 200
#define BME_XBEE_MS 200

// https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor?view=all
#define BNO_LOG_MS 20
#define BNO_XBEE_MS 20

time_t gps_timer = 0;
time_t bme_timer = 0;
time_t bno_timer = 0;

// RASPBERRY PI INFOS
// RUN PIN 14 -> côté USB

//- off -> éteint
//- idle -> Arduino et PI démarré
//- standby -> Arduino make pi in (sleep mode/steady state)
//- injected -> Levures injectés, en attente
//- ready -> both online and levure injectés
//- recording -> Start detecting decollage
//- landed -> When landed triggered -> emit GPS / (son)

// enum State
// {
//     s_IDLE = 1,
//     s_STANDBY = 2,
//     s_READY = 3,
//     s_RECORDING = 4,
//     s_FLYING = 5,
//     s_LANDED = 6
// };

// const float TAKE_OFF_TIME_MS = 0.500;
// const float TAKE_OFF_ACCELERATION_G = 3.0f;
// const float FLYING_TIME_S = 10.0; // * 60; //TODO: Change this
// const float GPS_EMIT_DELAY_MS = 500;

// uint8_t state;
// time_t gps_timer = 0;
// time_t timer_takeoff = 0;

// TESTS DATA
// OrderEnum rfSignals[] = {GET_STATE, SHUTDOWN, GET_STATE, WAKE, GET_STATE, INJECT, GET_STATE, REC, GET_STATE};
// const int nbSignals = (sizeof(rfSignals) / sizeof(OrderEnum));

void setup()
{
    setupBuzzer();

    startBuzzing();
    delay(500);
    stopBuzzing();

    delay(5000);

    startBuzzing();
    delay(500);
    stopBuzzing();

    // Init timers
    bme_timer = 0;
    bno_timer = 0;
    gps_timer = 0;

    //State initialize
    // state = s_IDLE;

    // Initialise modules
    setupLogging();
    // setupBuzzer();
    setupLight();
    // setupXbee();
    setupBno();
    setupBme();
    // setupPi();

    // /* Display some basic information on this sensor */
    displaySensorDetails();

    startBuzzing();
    delay(500);
    stopBuzzing();
}

// void stateMachineRun(OrderEnum order);
// bool inject();
// void startRecording();
// void stopRecording();
// bool detectLiftoff();

void loop()
{
    lightOn();
    delay(2000);
    lightOff();
    delay(2000);

    // GPS
    time_t elapsed_time = millis();
    if (gps_timer == 0 || (elapsed_time - gps_timer) >= GPS_XBEE_MS)
    {
        gps_timer = millis();

        // TODO: get GPS data
        float altitude = 0.0;
        float latitude = 0.0;
        float longitude = 0.0;

#ifdef DEBUG
        Serial.print("GPS - altitude : ");
        Serial.print(altitude);
        Serial.print("\t latitude : ");
        Serial.print(altitude);
        Serial.print("\t longitude : ");
        Serial.println(altitude);
#endif

        // Log GPS
        logGPS(millis(), altitude, latitude, longitude);

        // Send GPS
        // sendXbee(createGpsPacket(altitude, latitude, longitude));
    }

    // BME
    elapsed_time = millis();
    if (bme_timer == 0 || (elapsed_time - bme_timer) >= BME_XBEE_MS)
    {
        bme_timer = millis();

        // get BME DATA
        float temperature = getTemperatureC();
        float pressure = getPressureP();
        float altitude = getAltitudeM();
        float humidity = getHumidity();

#ifdef DEBUG
        Serial.print("BME - temperature : ");
        Serial.print(temperature);
        Serial.print("\t pressure : ");
        Serial.print(pressure);
        Serial.print("\t humidity : ");
        Serial.print(humidity);
        Serial.print("\t altitude : ");
        Serial.println(altitude);
#endif

        // Log BME
        logBME(millis(), temperature, pressure, humidity, altitude);

        // Send GPS
        // sendXbee(createBMEPacket(temperature, pressure, humidity, appoxAltitude));
    }

    // BNO
    elapsed_time = millis();
    if (bno_timer == 0 || (elapsed_time - bno_timer) >= BNO_XBEE_MS)
    {
        bno_timer = millis();

        // Sample data
        sampleBNO();

        // get BNO data
        float orientation[3];
        float acceleration[3];
        int8_t temperature = getBNOTemperatureC();
        getOrientation(orientation);
        getAcceleration(acceleration);

#ifdef DEBUG
        Serial.print("BNO - temperature[°C] : ");
        Serial.print(temperature);
        Serial.print("\t orientation[x,y,z] : ");
        Serial.print(orientation[0]);
        Serial.print(" , ");
        Serial.print(orientation[1]);
        Serial.print(" , ");
        Serial.print(orientation[2]);
        Serial.print("\t acceleration : ");
        Serial.print(acceleration[0]);
        Serial.print(" , ");
        Serial.print(acceleration[1]);
        Serial.print(" , ");
        Serial.println(acceleration[2]);
#endif

        // Log BNO
        logBNO(millis(), temperature, orientation, acceleration);

        // Send BNO
        // sendXbee(createBNOPacket(temperature, orientation, acceleration));
    }

    // // Start sending GPS Data every ## MS
    // if (state >= s_READY)
    // {
    //     time_t elapsed_time = millis();
    //     if (gps_timer != 0 && (gps_timer - elapsed_time) >= GPS_EMIT_DELAY_MS)
    //     {
    //         //TODO: get GPS data
    //         sendXbee(createGpsPacket(0, 46.520250, 6.566673, 397));
    //         gps_timer = millis();
    //     }
    // }

    // TODO:Image transmitting system

    //     delay(10000);
    //     for (unsigned int i = 0; i < nbSignals; ++i)
    //     {
    //         lightOn();
    //         stateMachineRun(rfSignals[i]);
    //         delay(200);
    //         lightOff();
    //     }
    //     delay(1000);

    /*
     * TEST TEENSY 2 PI
     */

    // lightOn();
    // delay(500);
    // Serial.write("Send order\n");
    // sendPiOrder(PiOrder::GET_IMAGE_BYTES, "");

    // /*
    //  * TEST PI 2 TEENS
    //  */
    // lightOff();
    // delay(500);
    // Serial.write("Read order\n");
    // elapsed_time = millis();
    // Packet p;
    // do {
    //     if((millis() - elapsed_time) >= 500){
    //         Serial.println("Restart");
    //         return;
    //     }
    //     p = readPiData();
    // }
    // while(p.size <= 0);

    // Serial.print("size");
    // Serial.println(p.size);
    // for(int i=0;i<p.size;++i)
    // {
    //     Serial.print(p.data[i]);
    //     Serial.print(",");
    // }
    // Serial.println("");

    /*
     * TEST TEENSY 2 GS
     */

    // lightOn();
    // Serial.println("Send XBEE");
    // // sendXbee(nullptr, 0);
    // Packet packet = createEmptyPacket();
    // sendXbee(packet);
    // //free(packet.data);
    // Serial.println("Packet generated");

    // delay(2000);
    // lightOff();
    // delay(2000);

    // readXbee();

    // lightOn();
    // Serial.println("Send XBEE");
    // sendXbee(createStatePacket(state));
    // free(packet.data);
    // Serial.println("Packet generated");

    // delay(2000);
    // lightOff();
    // delay(2000);

    // displaySensorEvents();
    // displayBmeValues();
    // lightOff();

    // delay(200);

    // stateMachineRun(readRF());
    // delay(10);
}

// void stateMachineRun(OrderEnum order)
// {
//     //General orders
//     switch (order)
//     {
//     case GET_STATE:
//         Serial.print("STATE : ");
//         Serial.println(state);
//         sendXbee(createStatePacket(state));
//     }

//     switch (state)
//     {
//     case s_IDLE:
//         switch (order)
//         {
//         case SHUTDOWN:
//             shutdownPi();
//             state = s_STANDBY;
//             break;
//         case INJECT:
//             if (inject())
//             {
//                 state = s_READY;
//             }

//             break;
//         case BYPASS_INJECT:
//             state = s_READY;
//             break;
//         }
//         break;

//     case s_STANDBY:
//         switch (order)
//         {
//         case WAKE:
//             wakeUpPi();
//             state = s_IDLE;
//             break;
//         }
//         break;

//     case s_READY:
//         switch (order)
//         {
//         case REC:
//             startRecording();
//             state = s_RECORDING;
//             break;
//         case INJECT:
//             inject();
//             break;
//         }
//         break;

//     case s_RECORDING:
//         switch (order)
//         {
//         case GET_IMAGE:
//             //TODO:
//             break;
//         case ABORT:
//             stopRecording();
//             state = s_IDLE;
//             break;
//         }
//         //Start detecting lift off
//         if (detectLiftoff())
//         {
//             //After liftoff Start timer and when timer is over then switch to LANDED state
//             state = s_FLYING;
//         }
//         break;

//     case s_FLYING:
//         time_t elapsed_time = millis();
//         if (timer_takeoff != 0 && (elapsed_time - timer_takeoff) / 1000 >= FLYING_TIME_S)
//         {
//             state = s_LANDED;
//         }
//         break;

//     case s_LANDED:
//         //TODO: Start sending GPS Location (+ emit sound)
//         //startBuzzing();
//         delay(10);
//         //stopBuzzing();
//         state = s_IDLE;
//         break;
//     }
// }

// bool inject()
// {
//     //TODO: Inject code
//     return true;
// }

// void startRecording()
// {
//     sendPiOrder(PiOrder::START_RECCORD, "");
//     //TODO: Wait for a response ???
// }

// void stopRecording()
// {
//     sendPiOrder(PiOrder::START_RECCORD, "");
//     //TODO: Wait for a response ???
// }

// bool detectLiftoff()
// {
//     float acc = getAcceleration();
//     if (acc < TAKE_OFF_ACCELERATION_G)
//     {
//         timer_takeoff = millis();
//         return false;
//     }

//     // TODO: Add pressure diff detector

//     time_t elapsed_time = millis();
//     return (timer_takeoff != 0 && (elapsed_time - timer_takeoff) >= TAKE_OFF_TIME_MS);
// }
