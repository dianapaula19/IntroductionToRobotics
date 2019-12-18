#ifndef motor_h
#define motor_h

class LedControl;
class Motorcycle {
  public:
    int x;
    Motorcycle();
    void moveLeft(int, bool&);
    void moveRight(int, bool&);
    void light(LedControl& lc, int);
};



#endif
