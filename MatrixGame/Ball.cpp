#include "Configuration.h"
#include "Ball.h"
#include "LedControl.h"


Ball::Ball() {
  x = 4;
  y = 6;
  val = 1;
  up = false;
  hit = true;
  bounceUp = false;
  bounceDown = false;
}
void Ball::moveMiddle(bool (&matrix)[8][8]) {
  if (up == true) {
    --y;
    if (y < 1) {
      y = 0;
      up = !up;
    } 
  } else {
    ++y;
    if (y > 5) {
      y = 6;
      up = !up;
      hit = !hit;
    }
  }
   matrix[y][x] = 0;
}
void Ball::moveLeft(bool (&matrix)[8][8]) {

  if (up == true) {
    if (bounceUp == true) {
      ++x;
    } else {
      --x;
    }
    --y;
    if (y < 1) {
      up = !up;
      bounceUp = false;
    } else if (x < 1) {
      bounceUp = true;
      x = 0;
    } else if (x > 6) {
      x = 7;
    }
  } else {
    if (bounceDown == true) {
      --x;
    } else {
      ++x;
    }
    y++;
    if (y > 5) {
      up = !up;
      hit = !hit;
      bounceDown = false;
    } else if (x > 6) {
      bounceDown = true;
      x = 7;
    } else if (x < 1) {
      x = 0;
    }

  }
   matrix[y][x] = 0;

}
void Ball::moveRight(bool (&matrix)[8][8]) {
  if (up == true) {
    if (bounceUp == true) {
      --x;
    } else {
      ++x;
    }
    --y;
    if (y < 1) {
      bounceUp = false;
      up = !up;
    } else if (x > 6) {
      x = 7;
      bounceUp = true;
    } else if (x < 1) {
      x = 0;
    } 
  } else {
    if (bounceDown == true) {
      ++x;
    } else {
      --x;
    }
    y++;
    if (y > 5) {
      bounceDown = false;
      hit = !hit;
      up = !up;
    } else if (x < 1) {
      bounceDown = true;
      x = 0;
    } else if (x > 6) {
      x = 7;
    }
  }
  matrix[y][x] = 0;

}
void Ball::light(LedControl& lc, int state) {
  lc.setLed(0, y, x, state);
}
