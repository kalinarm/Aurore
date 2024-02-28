//mode.h
#ifndef MODE_H
#define MODE_H

#include <Arduino.h>


class Mode {
  protected:
    ServoMotor* motors;

    int intensity;
    int speed;
    int offset;
    float frequency;

  public:
    Mode(ServoMotor* _motors) {
      motors = _motors;
    }
    void configure(int _intensity, int _speed, int _offset, float _frequency = 1.0) {
      intensity = _intensity;
      speed = _speed;
      offset = _offset;
      frequency = _frequency;
    }
    virtual void enter() {}
    virtual void exit() {}
    virtual void step(float time) {}
};

#endif
