#ifndef setup_h
#define setup_h

class LiquidCrystal;



class Setup {
  
  public:
  int option;
  int level;
  int speed;
  bool pressedButton;
  bool back;
  Setup();
  void print(LiquidCrystal&);
  void printWhenButtonPressed(LiquidCrystal&, int&, bool&);
  void printLevel(LiquidCrystal&);
  void printSpeed(LiquidCrystal&);
  void modifyLevel(int, bool&, int&, float&, int&);
  void modifySpeed(int, bool&, float&);
  void modifyOption(int, bool&);

  
};







#endif
