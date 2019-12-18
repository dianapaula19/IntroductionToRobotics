#include "Motorcycle.h"
#include "Configuration.h"
#include "LedControl.h"

Motorcycle::Motorcycle() {
  x = 4;
}

void Motorcycle::moveLeft(int xValue, bool& joyMoved) {
  if (xValue < MIN_THRESHOLD && joyMoved == false) {
    --x;
    if (x < 2) {
      x = 1;
    }
    joyMoved = true;
  }
  
}
void Motorcycle::moveRight(int xValue, bool& joyMoved) {
  if (xValue > MAX_THRESHOLD && joyMoved == false) {
    ++x;
    if (x > 5) {
      x = 6;
    }
    joyMoved = true;
  }
}
void Motorcycle::light(LedControl& lc, int state) {
  lc.setLed(0, 7, x, state);
}
