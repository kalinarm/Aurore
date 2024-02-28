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

  //configure the stepper
  stepperMotor.setup();
  
  //configure the motors
  setupMotors();

  //print a summerize of motors configuration
  //printMotorDebug();
}

void loop() {
  
#ifdef SERIAL_CONTROL
  //receive and parse arguments of input from serial. If it's a valid command, it will call processInputCommand
  processInput();
#else
  //receive and parse arguments of input from dùx.
  loopDmx();
#endif

  stepperMotor.loop();

  //make the current mode update if one is defined
  if (currentMode) {
    currentMode->step(time);
    time += dt;

#ifdef DEBUG
    //for debug
    delay(500);
    //printMotorDebug();
    printMotorArrayDebug();
#else
    //delay(20);
#endif
  }
}
