//servoMotor.h
#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <AccelStepper.h>
#include "constants.h"

#define CALIB_OFF 0
#define CALIB_PHASE_1 1
#define CALIB_PHASE_2 2

class StepperMotorControl {
    AccelStepper stepper;

    int m_sens;
    int m_enablePin;
    int m_limitPin;

    int m_isCalibrating = CALIB_OFF;

    int m_value;
    int m_speed;

  public:
    StepperMotorControl(int enablePin, int stepPin, int dirPin, int limitPin, int invert) {
      m_enablePin = enablePin;
      m_limitPin = limitPin;
      m_sens = invert;

      pinMode(m_enablePin, OUTPUT);

#ifdef USE_LIMIT_SWITCH_PULL_UP
      pinMode(m_limitPin, INPUT_PULLUP);
#else
      pinMode(m_limitPin, INPUT);
#endif


      stepper = AccelStepper(AccelStepper::DRIVER, stepPin, dirPin);
    }

    void setup() {
      stepper.setMaxSpeed(STEPPERS_MAX_SPEED);
      stepper.setAcceleration(STEPPERS_ACCELERATION);
      m_speed = 0;
    }

    void setActive(bool active) {
      if (active) {
        digitalWrite(m_enablePin, LOW);
      } else {
        digitalWrite(m_enablePin, HIGH);
      }
    }

    bool checkSecurity() {
#ifdef USE_LIMIT_SWITCH_PULL_UP
      bool limitReached = digitalRead(m_limitPin);
#else
      bool limitReached = !digitalRead(m_limitPin);
#endif

      return limitReached;
    }

    void loop() {
      if (loopCalibrating()) {
        return;
      }
      if (checkSecurity()) {
        stepper.stop();
        return;
      }
      stepper.runSpeedToPosition();
    }

    bool loopCalibrating() {
      if (!isCalibrating())
        return false;

      switch (m_isCalibrating) {
        case CALIB_PHASE_1:
          if (checkSecurity()) {
            //finish phase 1, switch to phase 2
            stepper.stop();
            m_isCalibrating = CALIB_PHASE_2;
            stepper.setCurrentPosition(0);
            stepper.moveTo(CALIB_STEPS_AFTER * m_sens);
            stepper.setSpeed(CALIB_SPEED);
          }
          setActive(true);
          stepper.move(-m_sens * 10);
          stepper.setSpeed(CALIB_SPEED);
          stepper.runSpeedToPosition();
          break;
        case CALIB_PHASE_2:
          stepper.runSpeedToPosition();
          if (stepper.distanceToGo() == 0) {
            stepper.stop();
            stopCalibrating();
          }
          break;
      }
    }

    //start the calibration state
    void startCalibrating() {
#ifdef DEBUG
      Serial.print("start calibration");
#endif
      m_isCalibrating = CALIB_PHASE_1;
    }

    // stop the calibration state
    void stopCalibrating() {
      m_isCalibrating = CALIB_OFF;
    }

    bool isCalibrating() {
      return m_isCalibrating != CALIB_OFF;
    }

    void printDebug() {
      println(String("stepper ") + " value=" + m_value + " speed=" + m_speed);
    }

    void setCmd(int sensCmd, int posCmd, int calibrateCmd) {
      if (sensCmd <= 20) {
        stepper.stop();
        setActive(false);
        stopCalibrating();
        return;
      }

      setActive(true);

      if (!isCalibrating() && calibrateCmd > 250) {
        startCalibrating();
        return;
      }

      int  speed = map(sensCmd, 21, 255, 0, STEPPERS_MAX_SPEED);
      long pos = m_sens * map(posCmd, 0, 255, 0.0, STEPPERS_STEPS_DISTANCE);
      stepper.moveTo(pos);
      stepper.setSpeed(speed);

#ifdef DEBUG
      Serial.print("pos=");
      Serial.print(pos);
      Serial.print(" speed=");
      Serial.println(speed);
#endif
    }
};


#endif
