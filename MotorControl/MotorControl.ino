/*
   Motor Control

   See the readme.md file in this folder

   Allow to control a stepper motor and a a bunch of servo motors
   commands come from a DMX shield of for serial port

   Project developped for Ersatz by kalinarm (kalinarm@gmail.com)

   to setup correctly this project, you have to install some librairies with the embeded library manager
   - Adafruit Motor Shield library
   - Adafruit PWM Servo Driver library
   - AccelStepper
   - DMX Lib : https://sourceforge.net/projects/dmxlibraryforar/files/

   Go to tab constants.h to configure this project
*/

//global time variable
float s_time = 0;

#include <Arduino.h>
#include "constants.h"
#include "helpers.h"
#include "servoMotor.h"
#include "modes.h"

#ifdef SERIAL_CONTROL
#include "input.h"
#else
#include "dmx.h"
#endif


void setup() {

#ifdef SERIAL_CONTROL
  //initialize serial connection
  Serial.begin(SERIAL_SPEED);
  //log version if in DEBUG mode
  Serial.println("motors control initialization");
  Serial.println(VERSION);
  Serial.println("> send ? for help");
#else
  //or initialize dmx connection
  setupDmx();
#endif

#ifdef USE_STEPPER_MOTOR
  //configure the stepper
  stepperMotor.setup();
#endif

#ifdef USE_SERVO_MOTORS
  //configure the motors
  setupMotors();

  //print a summerize of motors configuration
  //printMotorDebug();
#endif
}

void loop() {
#ifdef SERIAL_CONTROL
  //receive and parse arguments of input from serial. If it's a valid command, it will call processInputCommand
  processInput();
#else
  //receive and parse arguments of input from dmx.
  loopDmx();
#endif

#ifdef USE_STEPPER_MOTOR
  stepperMotor.loop();
#endif

#ifdef USE_SERVO_MOTORS
  //make the current mode update if one is defined
  if (currentMode) {
    currentMode->step(s_time);
  }
#endif

#ifdef DEBUG
  //for debug
  delay(500);
  //printMotorDebug();
  printMotorArrayDebug();
#else
  //delay(20);
  s_time += dt;
#endif
}
