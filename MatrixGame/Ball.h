#ifndef ball_h
#define ball_h
class LedControl;

class Ball {
  public:
    int x;
    int y;
    int val;
    bool up;
    bool hit;
    bool bounceUp;
    bool bounceDown;
    Ball();
    void light(LedControl&, int);
    void moveMiddle(bool (&matrix)[8][8]);
    void moveLeft(bool (&matrix)[8][8]);
    void moveRight(bool (&matrix)[8][8]);
  
};





#endif
