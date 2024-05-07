//control.h
#ifndef CONTROL_H
#define CONTROL_H

#include "stepperMotor.h"



//define stepper motor
StepperMotorControl stepperMotor;
//define servo motors
ServoMotor motors[MOTOR_COUNT];

//a pointer to one of the nodes
Mode* currentMode;
Mode* lastMode;

//define modes
ModeZero modeZero(motors);
ModeUniform modeUniform(motors);
ModeSinusX modeSinusX(motors);
ModeSinusY modeSinusY(motors);
ModeSea modeSea(motors);
ModeRandom modeRandom(motors);
ModeIcePack modeIcePack(motors);
ModeWaveX modeWaveX(motors);
ModeWaveY modeWaveY(motors);
ModeIcePack2 modeIcePack2(motors);

//choose and setup current mode with arguments
void processCmdMode(int mode, int intensity, int speed, int offset) {
#ifdef USE_SERVO_MOTORS
  //choose mode
  if (mode >= 255) {
    return;
  }else if (mode > 100) {
    currentMode = &modeIcePack2;
  } else if (mode > 90) {
    currentMode = &modeSinusX;
  } else if (mode > 80) {
    currentMode = &modeSinusY;
  } else if (mode > 70) {
    currentMode = &modeSea;
  }  else if (mode > 60) {
    currentMode = &modeRandom;
  } else if (mode > 50) {
    currentMode = &modeIcePack;
  } else if (mode > 40) {
    currentMode = &modeWaveX;
  } else if (mode > 30) {
    currentMode = &modeWaveY;
  } else if (mode > 20) {
    currentMode = &modeUniform;
  } else {
    currentMode = &modeZero;
  }

  //if no mode defined, we exit the function
  if (!currentMode) return;

  if (currentMode != lastMode) {
    s_time = 0.0;
    lastMode = currentMode;
    currentMode->configure(intensity, speed, offset);
    currentMode->enter();
    return;
  }

  //else we setup mode
  currentMode->configure(intensity, speed, offset);
#endif
}

void processCmdStepper(int move, int calib) {
#ifdef USE_STEPPER_MOTOR
if (calib > 200) {
  stepperMotor.setCalib();
}else {
   stepperMotor.setCmd(move);
}
#ifdef DEBUG
  Serial.print("stepper move=");
  Serial.print(move);
#endif
#endif
}

void printMotorDebug() {
  for (int i = 0; i < MOTOR_COUNT; ++i) {
    motors[i].printDebug();
  }
  println("");
}

void printMotorArrayDebug() {
#ifdef DEBUG
  for (int j = 0; j < Y_COUNT; ++j) {
    for (int i = 0; i < X_COUNT; ++i) {
      Serial.print (motors[GridToArrayCoord(i, j)].getValue());
      Serial.print(" ");
    }
    Serial.println();
  }
  Serial.println();
#endif
}

void setupMotors() {
  ServoMotor::setupDrivers();
  for (int i = 0; i < MOTOR_COUNT; ++i) {
    motors[i].configure(i, ArrayToGridCoordX(i), ArrayToGridCoordY(i));
  }
}

#endif
