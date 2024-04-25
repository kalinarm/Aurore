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

#define INTERNAL_LED 13


///////////////Global Config///////////////
#define MOTOR_RANGE_MM 1350

///////////////Motors Config///////////////

#define STEPS_PER_REVOLUTION 400
#define MM_PER_REVOLUTION 31.4

#define STEPPERS_STEPS_DISTANCE (MOTOR_RANGE_MM * (STEPS_PER_REVOLUTION / MM_PER_REVOLUTION))

#define STEPPERS_MAX_SPEED 900
#define STEPPERS_ACCELERATION 500

#define CALIB_SPEED 100
#define CALIB_STEPS_AFTER 50

#define STEPPER_A_ENABLE 8
#define STEPPER_A_STEP 9
#define STEPPER_A_DIR 10
#define STEPPER_A_LIMIT 5

#define STEPPER_A_INVERT 1

#define STEPPER_B_ENABLE 11
#define STEPPER_B_STEP 12
#define STEPPER_B_DIR 13
#define STEPPER_B_LIMIT 6

#define STEPPER_B_INVERT -1

//#define USE_LIMIT_SWITCH_PULL_UP // or pull down by default

////////////////DMX Config/////////////////
// first adresse of the board
#define DMX_START_CHANNEL  1 // for example 10 ,20 ,30 for the 3 grids
//count off reserverd channel
#define DMX_CHANNELS_COUNT   6 

///////////////GPIO Config/////////////////

#endif
