//servoMotor.h
#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#include "helpers.h"

#define SERVOMIN  210 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  520 // this is the 'maximum' pulse length count (out of 4096)

Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver(0x40);//First controller
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41);//second controller

class ServoMotor {
    int m_goal;
  public:
    //global index of the motor
    int m_index;
    //index for the driver
    int m_localIndex;
    //logic coordinate, in XY plane
    int m_x;
    int m_y;
    int m_value;
    //real worls coordinates
    float globalX;
    float globalY;
    bool invert;

    Adafruit_PWMServoDriver pwm;

  public:
    ServoMotor() {

    }
    void configure(int index, int x, int y) {
      m_x = x;
      m_y = y;
      //compute real world coordinate
      globalX = ((float)x) + GRID_X ;
      globalY = ((float)y) + ((x%2) ? 0.0 : 0.5);
      //choose the drive for this motor
      //and transform index to index local to the driver
      m_index = index;
      if (m_index >= 14) {
        pwm = pwm1;
        m_localIndex = m_index - 14;
      } else {
        pwm = pwm0;
        m_localIndex = m_index;
      }
      invert = (m_index > 13) ? true : false;
    }
    void setValue(int value)
    {
      m_value = constrain(value, MOTOR_MIN, MOTOR_MAX);
      setServoPosition();
    } 
    void setValueNorm(float value)
    {
      m_value = map(value, 0.0, 1.0, MOTOR_MIN, MOTOR_MAX);
      setServoPosition();
    }
    int getValue() {
      return m_value;
    }
    void setGoal(int value) {
      m_goal = constrain(value, MOTOR_MIN, MOTOR_MAX);
    }
    int getGoal() {
      return m_goal;
    }
    bool stepToGoal(float speed) {
      setValue(m_value + ((float)(m_goal - m_value)) * speed);
      return abs(m_value - m_goal) < 10;
    }

    void printDebug() {
      println(String("motor ") + m_x + " " + m_y + " val=" + m_value);
    }

  private:
    void setServoPosition() {
      pwm.setPWM(m_localIndex, 0, angleToPulse(invert ? MOTOR_MAX - m_value : m_value));
    }

  public:
    static void setupDrivers() {
      pwm0.begin();
      pwm0.setPWMFreq(50);  // Analog servos run at ~60 Hz updates for the first controller
      pwm1.begin();
      pwm1.setPWMFreq(50);
    }
    static int angleToPulse(int ang) {
      int pulse = map(ang, MOTOR_MIN, MOTOR_MAX, SERVOMIN, SERVOMAX); // map angle of 0 to 180 to Servo min and Servo max
      return pulse;
    }
};



#endif
