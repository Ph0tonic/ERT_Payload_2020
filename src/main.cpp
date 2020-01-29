#include <Arduino.h>
#include <time.h>

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
    s_OFF,
    s_IDLE,
    s_STANDBY,
    s_INJECTED,
    s_READY,
    s_RECORDING,
    s_FLYING,
    s_LANDED
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
const float FLYING_TIME_SEC = 10.0 * 60;

uint8_t state = s_OFF;
time_t timer_liftoff = 0;
time_t elapsed_time = 0;

void setup()
{
    setupPi();
    setupBuzzer();
    setupLight();
    setupBno();
    setupBme();

    // /* Use external crystal for better accuracy */
    // bno.setExtCrystalUse(true);

    // /* Display some basic information on this sensor */
    displaySensorDetails();
}

void loop()
{
    delay(1000);
    lightOn();

    delay(500);
    displaySensorEvents();
    displayBmeValues();
    lightOff();

    delay(200);

    //state_machine_run(read_rf());

    delay(10);
}

// void state_machine_run(uint8_t rf_signal) {
//   switch(state) {
//     case s_OFF:
//       //TODO
//       switch(rf_signal) {
//         case WAKE:
//           init();
//           state = s_IDLE;
//           break;
//       }
//       break;

//     case s_STANDBY:
//       //TODO
//       switch(rf_signal) {
//         case WAKE:
//           wake_pi();
//           state = s_IDLE;
//           break;
//       }
//       break;

//     case s_IDLE:
//       //TODO
//       switch(rf_signal) {
//         case SHUTDOWN:
//           shutdown_pi();
//           state = s_OFF;
//           break;
//         case INJECT:
//           inject();
//           state = s_INJECTED;
//           break;
//         case BYPASS_INJECT:
//           state = s_READY;
//           break;
//       }
//       //TODO
//       break;

//     case s_INJECTED:
//       //TODO wait confirm injection is OK
//       break;

//     case s_READY:
//       switch(rf_signal) {
//         case REC:
//           start_recording();
//           state = s_RECORDING;
//           break;
//       }
//       //TODO
//       break;

//     case s_RECORDING:
//       switch(rf_signal) {
//         case ABORT:
//           stop_recording();
//           state = s_IDLE; //TODO IDLE or StandBy ? -> if standby then set pi to sleeping mode
//           break;
//       }
//       //TODO Start detecting lift off
//       if(detect_liftoff()) {
//         //TODO After liftoff Start timer and when timer is over then switch to LANDED state
//         time(&timer_liftoff);
//         state = s_FLYING;
//       }
//       break;

//     case s_FLYING:
//       time(&elapsed_time);
//       if(timer_liftoff != 0 && difftime(timer_liftoff,elapsed_time) >= FLYING_TIME_SEC) {
//         state = s_LANDED;
//       }
//       break;

//     case s_LANDED:
//       //TODO Start sending GPS Location (+ emit sound)
//       break;
//   }
// }

// void init() {

// }

// void inject() {

// }

// void start_recording() {

// }

// void stop_recording() {

// }

// SignalRF_enum read_rf() {
//   return NONE;
// }

// void wake_pi() {
//   digitalWrite(pi_pin, LOW);
// }

// void shutdown_pi() {
//   digitalWrite(pi_pin, HIGH);
// }

// bool detect_liftoff() {
//   return false;
// }

// void sonor_signal_state() {
//   switch(state) {
//     case s_OFF:
//       //TODO
//       break;

//     case s_IDLE:
//       //TODO
//       break;

//     case s_STANDBY:
//       //TODO
//       break;

//     case s_INJECTED:
//       //TODO
//       break;

//     case s_READY:
//       //TODO
//       break;

//     case s_RECORDING:
//       //TODO
//       break;

//     case s_LANDED:
//       //TODO
//       break;
//   }
// }
