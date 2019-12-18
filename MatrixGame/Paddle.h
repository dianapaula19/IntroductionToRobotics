#ifndef paddle_h
#define paddle_h

class LedControl;

class Paddle {
  public:
    int pos;
    Paddle(int screen_width);
    void moveLeft(LedControl& lc);
    void moveRight(LedControl& lc);
    void light(LedControl& lc, int);
    private:
    int screen_width_;
   
};

#endif
