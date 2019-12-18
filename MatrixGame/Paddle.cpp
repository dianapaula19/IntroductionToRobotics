#include "Paddle.h"
#include "Configuration.h"
#include "LedControl.h"

Paddle::Paddle(int screen_width): screen_width_(screen_width) {
  pos = screen_width_ / 2 - 1;  
}
void Paddle::moveLeft(LedControl& lc) {
  if (pos > -1) {
    this->light(lc, LOW);
    --pos;
    this->light(lc, HIGH);
  }
}
void Paddle::moveRight(LedControl& lc) {
  if (pos + 2 < screen_width_) {
    this->light(lc, LOW);
    ++pos;
    this->light(lc, HIGH);
  } 
}

void Paddle::light(LedControl& lc, int state) {
  lc.setLed(0, 7, pos, state);
  lc.setLed(0, 7, pos + 1, state);
  lc.setLed(0, 7, pos + 2, state);
  
}
