//modes.h
#ifndef MODES_H
#define MODES_H

#include "mode.h"
//#include "noise.h"

// a mode that set all servos to zero
class ModeZero : public Mode {
  public :
    ModeZero(ServoMotor* _motors) : Mode(_motors) { }

    void enter() {
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        motors[i].setValue(MOTOR_RANGE * 0.5);
      }
    }
};

//mode that set all servos to offset
class ModeUniform : public Mode {
  public :
    ModeUniform(ServoMotor* _motors) : Mode(_motors) { }

    void step(float time) {
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        motors[i].setValue(offset);
      }
    }
};

//simulate a sea
class ModeSea : public Mode {
  public :
    ModeSea(ServoMotor* _motors) : Mode(_motors) { }

    void step(float time) {
      float index;
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        index = motors[i].globalX + motors[i].globalY;
        motors[i].setValue(offset
                           + intensity * sin((time * speed * 0.1) + index)
                           + 0.5 * intensity * sin((time * speed * 1.7) + (index)));
      }
    }
};

class ModeWaveX : public Mode {
  public :
    ModeWaveX(ServoMotor* _motors) : Mode(_motors) {
      frequency = 1.0;
    }

    void step(float time) {
      float t = 5.0 - time * speed;
      float term = t * 0.1;
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        motors[i].setValue(offset + intensity * sin(term + motors[i].globalX) / (term + motors[i].globalX));
      }
      if (time>5) time = 0;
    }
};

class ModeWaveY : public Mode {
  public :
    ModeWaveY(ServoMotor* _motors) : Mode(_motors) {
      frequency = 1.0;
    }

    void step(float time) {
      float t = 5.0 - time * speed;
      float term = t * 0.1;
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        motors[i].setValue(offset + intensity * sin(term + motors[i].globalY) / (term + motors[i].globalY));
      }
      if (time>5) time = 0;
    }
};

class ModeSinusX : public Mode {
  public :
    ModeSinusX(ServoMotor* _motors) : Mode(_motors) {
      frequency = 1;
    }

    void step(float time) {
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        motors[i].setValue(offset + intensity * sin((time * speed * 0.1) + motors[i].globalX));
      }
    }
};

class ModeSinusY : public Mode {
  public :
    ModeSinusY(ServoMotor* _motors) : Mode(_motors) { }

    void step(float time) {
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        motors[i].setValue(offset + intensity * sin((time * speed * 0.1) + motors[i].globalY));
      }
    }
};

/*class ModePerlin : public Mode {
  public :
    ModePerlin(ServoMotor* _motors) : Mode(_motors) { }

    void step(float time) {
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        motors[i].setValue(int(PerlinNoise2(motors[i].globalX, motors[i].globalY, 0.25, 3) * 128 + 128));
      }
    }
  };*/

// MODE Random
// a random position for each motor.
// when a motor reaches it's position
// it picks a new random position
class ModeRandom : public Mode {
    int goal = 0;
  public :
    ModeRandom(ServoMotor* _motors) : Mode(_motors) { }

    void step(float time) {
      int minVal = MOTOR_RANGE * 0.5  - intensity * 0.01 * MOTOR_RANGE  * 0.5 + offset;
      int maxVal = MOTOR_RANGE * 0.5  + intensity * 0.01 * MOTOR_RANGE  * 0.5 + offset;
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        //advance to goal position and choose a new goal if on goal pos
        if (motors[i].stepToGoal(speed * 0.01)) {
          motors[i].setGoal(random(minVal, maxVal));
        }
      }
    }
};


// MODE IcePack
//L'idée est de sculpter le tissu pour faire comme une maquette de banquise.
//Enclenchement du/des moteur pas à pas pour créer un volume central.
//Petite animation avec des "effondrement de glace". Un mouvement de cerveau moteur dans un temps aléatoire avec un choix de moteur aléatoire.
class ModeIcePack : public Mode {
  public :
    ModeIcePack(ServoMotor* _motors) : Mode(_motors) { }
    void enter() {
      int val;
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        motors[i].setValue(random(MOTOR_MIN, MOTOR_MAX));
        motors[i].setGoal(random(0, 100));
      }
    }

    void step(float time) {
#ifdef DEBUG
      Serial.print("mode IcePack");
      Serial.print(" offset=");
      Serial.print(offset);
      Serial.println(offset);
#endif
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        if (motors[i].getGoal() < offset) {
          motors[i].setValue(0);
        }
      }
    }
};
#endif
