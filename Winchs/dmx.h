//dmx.h
#ifndef DMX_H
#define DMX_H

#include <Conceptinetics.h>
#include "control.h"

int commands[DMX_CHANNELS_COUNT];

bool hasInputChanged = false;

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
    val = dmx_slave.getChannelValue (i + 1);

    if (val != commands[i]) {
      commands[i] = val;
      hasInputChanged = true;
    }
  }

  if (hasInputChanged) {
    processCmdStepperA(commands[0], commands[1], commands[2]);
    processCmdStepperB(commands[3], commands[4], commands[5]);
    hasInputChanged = false;
  }
}
#endif
