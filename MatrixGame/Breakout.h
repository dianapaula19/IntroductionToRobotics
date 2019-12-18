#ifndef breakout_h
#define breakout_h
#include "Configuration.h"
#include "Paddle.h"
#include "Ball.h"
class LedControl;

class Breakout {
  public:
    bool matrix[8][8] = {
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 1, 1, 1, 1},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0}
    };
    Breakout();
    unsigned long wait = 0;
    unsigned long millis;
    bool restart = false;
    bool left = false;
    bool middle = false;
    bool right = false;
    void setup(LedControl& lc);
    bool joyMoved;
    bool ok;
    Paddle p{8};
    Ball b;
    void print(LedControl& lc, bool matrix[8][8]);
    void startGame(LedControl& lc, float speed);
    void movePaddle(LedControl& lc);
    bool finishedGame();
    void bricks(LedControl& lc);
    void resetBricks();
    void stop(LedControl& lc);


};










#endif
