//helpers.h
#ifndef HELPERS_H
#define HELPERS_H

// log a message if DEBUG is defined
void print(String message) {
#ifdef DEBUG
  Serial.print(message);
#endif
}
void println(String message) {
#ifdef DEBUG
  Serial.println(message);
#endif
}

// log a message if DEBUG is defined
void debug(String message) {
#ifdef DEBUG
  Serial.println("[DEBUG] " + message);
#endif
}


#endif
