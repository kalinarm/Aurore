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

    float intensityNorm() {
      return mapping(intensity,0.0,100.0,0.0,1.0);
    }
    float speedNorm() {
      return mapping(speed,0.0,100.0,0.0,2.0);
    }

    float mapping(float x, float in_min, float in_max, float out_min, float out_max) {
      return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }
};

#endif
