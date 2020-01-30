#include <Arduino.h>

#include "pi.h"
#include "buzzer.h"
#include "led.h"
#include "bno.h"
#include "bme.h"

// RASPBERRY PI INFOS
// RUN PIN 14 -> côté USB

//- off -> éteint
//- idle -> Arduino et PI démarré
//- standby -> Arduino make pi in (sleep mode/stady state)
//- injected -> Levures injectés, en attente
//- ready -> both online and levure injectés
//- recording -> Start detecting decollage
//- landed -> When landed triggered -> emit GPS / (son)
enum State_enum
{
    s_IDLE = 1,
    s_STANDBY = 2,
    s_READY = 3,
    s_RECORDING = 4,
    s_FLYING = 5,
    s_LANDED = 6
};
enum SignalRF_enum
{
    NONE,
    GET_STATE,
    SHUTDOWN,
    WAKE,
    INJECT,
    BYPASS_INJECT,
    REC,
    ABORT
};

const float TAKE_OFF_TIME_SEC = 0.500;
const float FLYING_TIME_SEC = 10.0;// * 60; //TODO: Change this

uint8_t state;
time_t timer_liftoff = 0;
time_t elapsed_time = 0;

void setup()
{
    //State initialize
    state = s_IDLE;

    //Initialise modules
    setupPi();
    setupBuzzer();
    setupLight();
    setupBno();
    setupBme();

    // /* Display some basic information on this sensor */
    displaySensorDetails();
}

SignalRF_enum rfSignals[] = {GET_STATE, SHUTDOWN, GET_STATE, WAKE, GET_STATE, INJECT, GET_STATE, REC, GET_STATE};
const int nbSignals = (sizeof(rfSignals) / sizeof(SignalRF_enum));

void state_machine_run(uint8_t rf_signal);
bool inject();
void start_recording();
void stop_recording();
SignalRF_enum read_rf();
bool detect_liftoff();
void sonor_signal_state();

void loop()
{
    delay(10000);
    for (unsigned int i = 0; i < nbSignals; ++i)
    {
        lightOn();
        state_machine_run(rfSignals[i]);
        delay(200);
        lightOff();
    }
    delay(1000);

    // delay(500);
    // displaySensorEvents();
    // displayBmeValues();
    // lightOff();

    // delay(200);

    // state_machine_run(read_rf());
    // delay(10);
}

void state_machine_run(uint8_t rf_signal)
{
    switch (rf_signal)
    {
    case GET_STATE:
        Serial.print("STATE : ");
        Serial.println(state);
    }
    switch (state)
    {
    case s_IDLE:
        //TODO
        switch (rf_signal)
        {
        case SHUTDOWN:
            shutdownPi();
            state = s_STANDBY;
            break;
        case INJECT:
            if (inject())
            {
                state = s_READY;
            }
            else
            {
                //TODO Signals failure of injection
            }

            break;
        case BYPASS_INJECT:
            state = s_READY;
            break;
        }
        //TODO
        break;

    case s_STANDBY:
        //TODO
        switch (rf_signal)
        {
        case WAKE:
            wakeUpPi();
            state = s_IDLE;
            break;
        }
        break;

    case s_READY:
        switch (rf_signal)
        {
        case REC:
            start_recording();
            state = s_RECORDING;
            break;
        }
        //TODO
        break;

    case s_RECORDING:
        switch (rf_signal)
        {
        case ABORT:
            stop_recording();
            state = s_IDLE; //TODO IDLE or StandBy ? -> if standby then set pi to sleeping mode
            break;
        }
        //TODO Start detecting lift off
        if (detect_liftoff())
        {
            //TODO After liftoff Start timer and when timer is over then switch to LANDED state
            timer_liftoff = millis();
            state = s_FLYING;
        }
        break;

    case s_FLYING:
        elapsed_time = millis();
        if (timer_liftoff != 0 && (elapsed_time - timer_liftoff)/1000 >= FLYING_TIME_SEC)
        {
            state = s_LANDED;
        }
        break;

    case s_LANDED:
        //TODO Start sending GPS Location (+ emit sound)
        //startBuzzing();
        delay(10);
        //stopBuzzing();
        state = s_IDLE;
        break;
    }
}

bool inject()
{
    return true;
}

void start_recording()
{
}

void stop_recording()
{
}

SignalRF_enum read_rf()
{
    return NONE;
}

bool detect_liftoff()
{
    return true;
}

void sonor_signal_state()
{
    switch (state)
    {
    case s_IDLE:
        //TODO
        break;

    case s_STANDBY:
        //TODO
        break;

    case s_READY:
        //TODO
        break;

    case s_RECORDING:
        //TODO
        break;

    case s_LANDED:
        //TODO
        break;
    }
}
