
#include <Arduino.h>
#include "constants.h"
#include "helpers.h"

#ifdef SERIAL_CONTROL
#include "input.h"
#else
#include "dmx.h"
#endif


void setup() {
  pinMode(INTERNAL_LED, OUTPUT);
  digitalWrite(INTERNAL_LED, HIGH);
  delay(200);
  digitalWrite(INTERNAL_LED, LOW);

#ifdef SERIAL_CONTROL
  Serial.begin(SERIAL_SPEED);
  Serial.println("Winchs control");
  Serial.println(VERSION);
  Serial.println("> send ? for help");
#else
  //or initialize dmx connection
  setupDmx();
#endif

  //configure the stepper
  stepperMotorA.setup();
  stepperMotorB.setup();
}

void loop() {
#ifdef SERIAL_CONTROL
  //receive and parse arguments of input from serial. If it's a valid command, it will call processInputCommand
  processInput();
#else
  //receive and parse arguments of input from dmx.
  loopDmx();
#endif

  stepperMotorA.loop();
  stepperMotorB.loop();

}
