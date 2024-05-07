//servoMotor.h
#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <AccelStepper.h>
#include "constants.h"

// Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper(AccelStepper::HALF4WIRE, 2, 4, 3, 5);

class StepperMotorControl {
    int m_value;
    int m_speed;

  public:
    StepperMotorControl() {
    
    }

    void setup() {
      stepper.setCurrentPosition(0);
      stepper.setMaxSpeed(350);
      stepper.setAcceleration(200);
      m_speed = 0;
    }

    void setCmd(int value) {
      if (value < 20) stop();
      else if (value < 126) setSpeed(1);
      else setSpeed(-1);
    }

    void setCalib() {
      m_speed = 0;
      stepper.moveTo(0);
    }

    void setSpeed(int speed) {
      m_speed = speed;
    }

    void stop() {
      m_speed = 0;
      stepper.stop();
    }

    void loop() {  
      if (m_speed > 0) {
        stepper.move(4096);
      }else  if (m_speed < 0) {
        stepper.move(-4096);
      }
      stepper.run();
    }
    
    void printDebug() {
      println(String("stepper ") + " value=" + m_value + " speed=" + m_speed);
    }
};


#endif
