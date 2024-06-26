//modes.h
#ifndef MODES_H
#define MODES_H

#include "mode.h"

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
    int lastOffset;
  public :
    ModeUniform(ServoMotor* _motors) : Mode(_motors) {
      lastOffset = 0;
    }
    void enter() {
      lastOffset = -1;
    }
    void step(float time) {
      if (offset == lastOffset) {
        return;
      }
      lastOffset = offset;

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
                           + intensity * sin(speed * 0.003 * (time + index)
                           + 0.5 * intensity * sin(speed * 0.001 *(time + index))));
      }
    }
};

class ModeWaveX : public Mode {
  public :
    ModeWaveX(ServoMotor* _motors) : Mode(_motors) {}

    void enter() {
      frequency = 15;
    }

    void step(float time) {
      float t = frequency - time;
      float term = t * 0.1 * speed;
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        motors[i].setValue(offset + intensity * sin(term + motors[i].globalX) / (term + motors[i].globalX));
      }
      if (s_time > 2 * frequency) s_time = 0;
    }
};

class ModeWaveY : public Mode {
  public :
    ModeWaveY(ServoMotor* _motors) : Mode(_motors) {}

    void enter() {
      frequency = 5;
    }

    void step(float time) {
      float t = frequency - time * speed;
      float term = t * 0.1;
      for (int i = 0; i < MOTOR_COUNT; ++i) {
        motors[i].setValue(offset + intensity * sin(term + motors[i].globalY) / (term + motors[i].globalY));
      }
      if (s_time > frequency) s_time = 0;
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
        if (motors[i].stepToGoal(speed * 0.001)) {
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
    int lastOffset;
  public :
    ModeIcePack(ServoMotor* _motors) : Mode(_motors) {
      lastOffset = 0;
    }
    void enter() {
      lastOffset = -1;
      int val;

      for (int i = 0; i < MOTOR_COUNT; ++i) {
        /* if (i == 6 || i == 2 || i == 7 || i == 9 || i == 12 || i == 22) {
           continue;
          }*/
        motors[i].setValue(MOTOR_RANGE * 0.5);
      }

      motors[5].setGoal(MOTOR_MAX);
      motors[1].setGoal(MOTOR_MAX);

      motors[6].setGoal(MOTOR_MIN);
      motors[8].setGoal(MOTOR_MIN);
      motors[11].setGoal(MOTOR_MIN);
      motors[21].setGoal(MOTOR_MIN);
    }

    void step(float time) {
      if (offset == lastOffset) {
        return;
      }
      lastOffset = offset;

      if (offset > 30) setMotorToGoal(8);
      if (offset > 60) setMotorToGoal(5);
      if (offset > 90) setMotorToGoal(11);
      if (offset > 120) setMotorToGoal(6);
      if (offset > 150) setMotorToGoal(21);
      if (offset > 180) setMotorToGoal(1);

    }

    void setMotorToGoal(int index) {
      motors[index].setValue(motors[index].getGoal());
    }
};


class ModeIcePack2 : public Mode {
    int lastOffset;
  public :
    ModeIcePack2(ServoMotor* _motors) : Mode(_motors) {
      lastOffset = 0;
    }
    void enter() {
      lastOffset = -1;
      int val;

      for (int i = 0; i < MOTOR_COUNT; ++i) {
        /* */
        motors[i].setValue(MOTOR_RANGE * 0.5);
      }

      motors[5].setGoal(MOTOR_MAX);
      motors[1].setGoal(MOTOR_MAX);

      motors[6].setGoal(MOTOR_MIN);
      motors[8].setGoal(MOTOR_MIN);
      motors[11].setGoal(MOTOR_MIN);
      motors[21].setGoal(MOTOR_MIN);
    }

    void step(float time) {


      for (int i = 0; i < MOTOR_COUNT; ++i) {
        if (i == 6 || i == 2 || i == 7 || i == 9 || i == 12 || i == 22) {
          continue;
        }
        motors[i].setValue(intensity * sin((time * speed * 0.001) + motors[i].globalY));
      }


      if (offset == lastOffset) {
        return;
      }
      lastOffset = offset;

      if (offset > 30) setMotorToGoal(8);
      if (offset > 60) setMotorToGoal(5);
      if (offset > 90) setMotorToGoal(11);
      if (offset > 120) setMotorToGoal(6);
      if (offset > 150) setMotorToGoal(21);
      if (offset > 180) setMotorToGoal(1);
    }

    void setMotorToGoal(int index) {
      motors[index].setValue(motors[index].getGoal());
    }
};
#endif
