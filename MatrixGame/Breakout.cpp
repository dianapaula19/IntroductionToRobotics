#include "Breakout.h"
#include "LedControl.h"

Breakout::Breakout() {
  wait = 0;
  restart = false;
  left = false;
  middle = false;
  right = false;
}
void Breakout::setup(LedControl& lc) {
  this->print(lc, matrix);
  p.light(lc, HIGH);
  b.light(lc, HIGH);
}
void Breakout::stop(LedControl& lc) {
  p.light(lc, LOW);
  b.light(lc, LOW);
}
void Breakout::movePaddle(LedControl& lc) {
  int xValue = analogRead(PIN_X);
  if (xValue < MIN_THRESHOLD && joyMoved == false) {
    p.moveLeft(lc);
    joyMoved = true;
  }
  if (xValue > MAX_THRESHOLD && joyMoved == false) {
    p.moveRight(lc);
    joyMoved = true;
  }
  if (xValue < MAX_THRESHOLD && xValue > MIN_THRESHOLD) {
    joyMoved = false;
  }
  
}
void Breakout::print(LedControl& lc, bool matrix[8][8]) {
  for(int i = 0; i < 8; ++i) {
    for(int j = 0; j < 8; ++j) {
      lc.setLed(0, i, j, matrix[i][j]); 
    }
  }
}
void Breakout::bricks(LedControl& lc) {
  for(int i = 0; i < 3; ++i) {
    for(int j = 0; j < 8; ++j) {
      if (matrix[i][j] == 0) {
      lc.setLed(0, i, j, matrix[i][j]); 
      }
    }
  }
}
bool Breakout::finishedGame() {
  for(int i = 0; i < 3; ++i) {
    for(int j = 0; j < 8; ++j) {
      if (matrix[i][j] == 1) {
        return false;
      }
    }
  }
  return true;
}
void Breakout::resetBricks() {
  for(int i = 0; i < 3; ++i) {
    for(int j = 0; j < 8; ++j) {
      matrix[i][j] = 3;
    }
  }
}
void Breakout::startGame(LedControl& lc, float speed) {
  unsigned long time = millis - wait;  
  if (time >= BALL_SPEED * speed) {
    if (restart == false) {
    if (b.hit == true) {
        left = false;
        middle = false;
        right = false;
       if (b.x == p.pos || b.x == p.pos - 1) {
        left = !left;
        b.light(lc, LOW);
        b.moveLeft(matrix);
        b.light(lc, HIGH);
        b.hit = !b.hit;
       } else if (b.x == p.pos + 1) {
        Serial.println(b.x);
        middle = !middle;
        b.light(lc, LOW);
        b.moveMiddle(matrix);
        b.light(lc, HIGH);
        b.hit = !b.hit;
       } else if (b.x == p.pos + 2 || b.x == p.pos + 3) {
        right = !right;
        b.light(lc, LOW);
        b.moveRight(matrix);
        b.light(lc, HIGH);
        b.hit = !b.hit;
       } else {
        restart = !restart;
       }
    } else {
      if (left == true) {
        b.light(lc, LOW);
        b.moveLeft(matrix);
        b.light(lc, HIGH);
      }
      if (middle == true) {
        b.light(lc, LOW);
        b.moveMiddle(matrix);
        b.light(lc, HIGH);
      }
      if (right == true) {
        b.light(lc, LOW);
        b.moveRight(matrix);
        b.light(lc, HIGH);
      }
      
    }
    } else {
      p.light(lc, LOW);
      p.pos = 3;
      p.light(lc, HIGH);
      b.light(lc, LOW);
      b.x = 4;
      b.y = 6;
      b.light(lc, HIGH);
      restart = !restart;
    }
    wait = millis;
  }
}
