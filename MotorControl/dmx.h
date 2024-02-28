//dmx.h
#ifndef DMX_H
#define DMX_H

#include <Conceptinetics.h>
#include "control.h"

int commands[DMX_CHANNELS_COUNT];

bool hasChangedStepper = false;
bool hasChangedServo = false;

#define STEPPER_COMMAND_INDEX 2

// Configure a DMX slave controller
DMX_Slave dmx_slave ( DMX_CHANNELS_COUNT );

void setupDmx() {
  // Enable DMX slave interface and start recording
  dmx_slave.enable ();
  dmx_slave.setStartAddress (DMX_START_CHANNEL);
}


void loopDmx() {

  int val;
  for (int i = 0; i < DMX_CHANNELS_COUNT ; ++i) {
    
    //val = map(dmx_slave.getChannelValue (i + 1),0,255,0,100);
    val = dmx_slave.getChannelValue (i + 1);
    
    if (val != commands[i]) {
      commands[i] = val;
      if (i < STEPPER_COMMAND_INDEX) {
        hasChangedStepper = true;
      } else {
        hasChangedServo = true;
      }
    }
  }

  if (hasChangedStepper) {
    processCmdStepper(commands[0]);
    hasChangedStepper = false;
  }
  if (hasChangedServo) {
    processCmdMode(commands[STEPPER_COMMAND_INDEX], commands[STEPPER_COMMAND_INDEX + 1], commands[STEPPER_COMMAND_INDEX + 2], commands[STEPPER_COMMAND_INDEX + 3]);
    hasChangedServo = false;
  }
}
#endif
