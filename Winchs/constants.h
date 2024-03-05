//constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

//////////////General Config///////////////
//#define DEBUG // uncomment to slow simulation, and have feedback on serial port
//#define SERIAL_CONTROL //uncomment to switch to serial control

#define VERSION "v0.9"

float dt = 0.01; // global speed multiplicator of servos mode

///////////////Serial Config///////////////
#define SERIAL_SPEED 9600

///////////////Motors Config///////////////

#define STEPPERS_MAX_SPEED 900
#define STEPPERS_ACCELERATION 500

#define CALIB_SPEED 100
#define CALIB_STEPS_AFTER 50

#define STEPPER_A_ENABLE 8
#define STEPPER_A_STEP 9
#define STEPPER_A_DIR 10
#define STEPPER_A_LIMIT 13
#define STEPPER_A_INVERT 1

#define STEPPER_B_ENABLE 2
#define STEPPER_B_STEP 3
#define STEPPER_B_DIR 4
#define STEPPER_B_LIMIT 12
#define STEPPER_B_INVERT -1

////////////////DMX Config/////////////////
// first adresse of the board
#define DMX_START_CHANNEL  1 // for example 10 ,20 ,30 for the 3 grids
//count off reserverd channel
#define DMX_CHANNELS_COUNT   10 

///////////////GPIO Config/////////////////

#endif
