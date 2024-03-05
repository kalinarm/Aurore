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
      pinMode(m_limitPin, INPUT);
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
      bool limitReached = digitalRead(m_limitPin);
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

      if (m_speed > 0) {
        stepper.move(m_speed * m_sens);
      } else  if (m_speed < 0) {
        stepper.move(-m_speed * m_sens);
      }
      stepper.run();
    }

    bool loopCalibrating() {
      if (!isCalibrating())
        return false;

      switch (m_isCalibrating) {
        case CALIB_PHASE_1:
          if (checkSecurity()) {
            stepper.stop();
            m_isCalibrating = CALIB_PHASE_2;
            stepper.setCurrentPosition(0);
            stepper.moveTo(CALIB_STEPS_AFTER * m_sens);
          }
          setActive(true);
          stepper.move(-CALIB_SPEED * m_sens);
          stepper.run();
          break;
        case CALIB_PHASE_2:
          stepper.run();
          if (stepper.distanceToGo() == 0) {
            setActive(false);
            m_isCalibrating = CALIB_OFF;
          }
          break;
      }
    }

    void setSpeed(int speed) {
      m_speed = speed;
    }

    void stop() {
      m_speed = 0;
      stepper.stop();
    }

    void startCalibrating() {
#ifdef DEBUG
      Serial.print("start calibration");
#endif
      m_isCalibrating = CALIB_PHASE_1;
    }

    void nextCalibratingPhase() {
      if (++m_isCalibrating > CALIB_PHASE_2) {
        m_isCalibrating = CALIB_OFF;
      }
    }

    bool isCalibrating() {
      return m_isCalibrating != CALIB_OFF;
    }

    void printDebug() {
      println(String("stepper ") + " value=" + m_value + " speed=" + m_speed);
    }

    void setCmd(int sensCmd, int speedCmd, int calibrateCmd) {
      //process sensCmd
      setActive(sensCmd > 20);
      if (sensCmd > 127) {
        setSpeed(map(speedCmd, 21, 255, 0, STEPPERS_MAX_SPEED));
      } else if (sensCmd > 20) {
        setSpeed(map(speedCmd, 21, 255, 0, -STEPPERS_MAX_SPEED));
      }

      if (!isCalibrating() && calibrateCmd > 250) {
        startCalibrating();
      }
    }
};


#endif
