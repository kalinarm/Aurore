//constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

//////////////General Config///////////////
//#define DEBUG // uncomment to slow simulation, and have feedback on serial port
//#define SERIAL_CONTROL //to uncomment to switch to serial control

#define VERSION "v1.2"

float dt = 0.01; // global speed multiplicator of servos mode

///////////////Grid Offset/////////////////
#define GRID_X 0 // 0 - 1 - 2 for the 3 grids

///////////////Serial Config///////////////
#define SERIAL_SPEED 9600

///////////////Motors Config///////////////
//Amount of motor in X
#define X_COUNT  9
//Amount of motor in Y
#define Y_COUNT  3
//for convencience
#define MOTOR_COUNT  X_COUNT * Y_COUNT

//minimum input of motor
#define MOTOR_MIN 0
//minimum output of motor
#define MOTOR_MAX 100
//for convencience
#define MOTOR_RANGE 100

////////////////DMX Config/////////////////
// first adresse of the board
#define DMX_START_CHANNEL  10 // for example 10 ,20 ,30 for the 3 grids
//count off reserverd channel
#define DMX_CHANNELS_COUNT   10 

///////////////GPIO Config/////////////////

#endif
