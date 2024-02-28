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

// Convert 2d coord to array index
int GridToArrayCoord(int x, int y) {
  return x + y * X_COUNT;
}
// Convert array index to x 2d coord
int ArrayToGridCoordX(int i) {
  return i % X_COUNT;
}
// Convert array index to y 2d coord
int ArrayToGridCoordY(int i) {
  return i / X_COUNT;
}


#endif
