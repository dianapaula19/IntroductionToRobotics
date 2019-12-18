#ifndef menu_h
#define menu_h
#include "Setup.h"
#include "Configuration.h"

class LiquidCrystal;


class Menu {
  public:
    Setup s;
    int option;
    int firstDigit;
    int secondDigit;
    int thirdDigit;
    bool startBreakout;
    bool startGameBreakout;
    bool stopBreakout;
    bool lost;
    bool won;
    bool waitDisplay;
    int timeLeft;
    float score;
    float highScore;
    float speed;
    bool pressedButton;
    unsigned long millis;
    unsigned long wait;
    unsigned long waitDigits;
    unsigned long waitKaneda;
    Menu();
    void modifyOption(int, bool&);
    void print(LiquidCrystal&);
    void printWhenButtonPressed(LiquidCrystal&);
    void printHighScore(LiquidCrystal&);
    void printStart(LiquidCrystal&);
    void printInfo(LiquidCrystal&);
    void changeTime();
};

#endif
