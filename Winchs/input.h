//input.h
#ifndef INPUT_H
#define INPUT_H

#include "control.h"


const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;

const byte MAX_ARGUMENTS = 6;
int commands[MAX_ARGUMENTS];

void setDefaultCommandArgument() {
  //A enable/sens
  commands[0] = 0;
  //A speed
  commands[1] = 127;
  //A calibrate
  commands[2] = 0;

  //B enable/sens
  commands[3] = 0;
  //B speed
  commands[7] = 127;
  //B calibrate
  commands[8] = 0;

}

void strToArguments(char* data) {
  int argIndex = 0;
  setDefaultCommandArgument();

  //decode arguments
  char * strToken = strtok (data, " " );
  commands[argIndex] = atoi(strToken);

  strToken = strtok ( NULL, " " );
  while ( strToken != NULL ) {
    commands[++argIndex] = atoi(strToken);
    strToken = strtok ( NULL, " " );
  }

#ifdef DEBUG
  Serial.print(argIndex);
  for (int i = 0; i <= argIndex; ++i) {
    Serial.print(" arg");
    Serial.print(i);
    Serial.print("=");
    Serial.print(commands[i]);
  }
  Serial.println();
#endif

  processCmdStepperA(commands[0], commands[1], commands[2]);
  processCmdStepperB(commands[3], commands[4], commands[5]);
}


void receiveInput() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void processInput() {
  receiveInput();
  if (newData == true) {
    print("received : ");
    println(receivedChars);
    newData = false;

    if (strlen(receivedChars) == 0) return;

    if (receivedChars[0] == '?') {
      Serial.println("to control a mode ,send a command in the format ");
      Serial.println("[mode] [intensity] [speed] [offset]");
      Serial.println("to control stepper ,send a command in the format ");
      Serial.println("110 [direction] [speed]");
      return;
    }

    strToArguments(receivedChars);
  }
}
#endif
