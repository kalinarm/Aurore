//input.h
#ifndef INPUT_H
#define INPUT_H

#include "control.h"


const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
const byte MAX_ARGUMENTS = 4;
int commands[MAX_ARGUMENTS];

void setDefaultCommandArgument() {
  //mode
  commands[0] = 0;
  //intensity
  commands[1] = 50;
  //speed
  commands[2] = 50;
  //offset
  commands[3] = 50;
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

  //process arguments
  if (commands[0] > 100) {
    //the input command is about stepper motor
    //move, speed
    if (argIndex < 1) {
      //set default move command top stop if argument not provided
      commands[1] = 0;
    }
    //the input command is about stepper
    processCmdStepper(commands[1]);
  } else {
    //the input command is about servo motors
    //int mode, int intensity, int speed, int offset
    processCmdMode(commands[0], commands[1], commands[2], commands[3]);
  }
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
