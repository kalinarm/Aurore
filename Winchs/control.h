//control.h
#ifndef CONTROL_H
#define CONTROL_H

#include "stepperMotor.h"

//define stepper motor
StepperMotorControl stepperMotorA(STEPPER_A_ENABLE, STEPPER_A_STEP, STEPPER_A_DIR, STEPPER_A_LIMIT, STEPPER_A_INVERT);
StepperMotorControl stepperMotorB(STEPPER_B_ENABLE, STEPPER_B_STEP, STEPPER_B_DIR, STEPPER_B_LIMIT, STEPPER_B_INVERT);

void processCmdStepperA(int sens, int speed, int calibrate) {
#ifdef DEBUG
  Serial.print("stepper A sens=");
  Serial.print(sens);
  Serial.print(" speed=");
  Serial.print(speed);
  Serial.print(" calibrate=");
  Serial.println(calibrate);
#endif
  stepperMotorA.setCmd(sens, speed, calibrate);
}

void processCmdStepperB(int sens, int speed, int calibrate) {
#ifdef DEBUG
  Serial.print("stepper B sens=");
  Serial.print(sens);
  Serial.print(" speed=");
  Serial.print(speed);
  Serial.print(" calibrate=");
  Serial.println(calibrate);
#endif
  stepperMotorB.setCmd(sens, speed, calibrate);
}

#endif
