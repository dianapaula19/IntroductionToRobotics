#include "Race.h"
#include "Configuration.h"
#include "LedControl.h"

Race::Race() {
  wait = 0;
  wait_m = 0;
  state = HIGH;
  rowScenery = 31;
  joyMoved = false;
}
void Race::move(LedControl& lc) {
  unsigned long time = millis - wait;
  int xValue = analogRead(PIN_X);
  m.light(lc, LOW);
  m.moveRight(xValue, joyMoved);
  m.moveLeft(xValue, joyMoved);
  if (xValue > MIN_THRESHOLD && xValue < MAX_THRESHOLD) {
    joyMoved = false;
  }
  m.light(lc, HIGH);
    if (time > SECOND) {
      for (int col = 0; col < 8; ++col) {
          matrix[0][col] = scenery[rowScenery][col];
      }
      for(int row = 7; row > 0; --row) {
        for(int col = 0; col < 8; ++col) {
          matrix[row][col] = matrix[row - 1][col];
        }
      }
      --rowScenery;
      if (rowScenery == -1) {
        won = true;
      }
      for (int col = 0; col < 8; ++col) {
          matrix[0][col] = scenery[rowScenery][col];
      }
      if (matrix[7][m.x] == 1) {
        lost = true;
      }
      this->print(lc, matrix);
      wait = millis;
    }
}
void Race::print(LedControl& lc, bool matrix[8][8]) {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      lc.setLed(0, i, j, matrix[i][j]);
    }
  }
}
void Race::setup(LedControl& lc) {
  lc.shutdown(0, false);
  lc.setIntensity(0, 2);
  lc.clearDisplay(0);
  this->print(lc, matrix);
  m.light(lc, HIGH);
}
