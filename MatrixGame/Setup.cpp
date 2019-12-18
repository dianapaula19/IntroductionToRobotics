#include "Configuration.h"
#include <LiquidCrystal.h>
#include "Setup.h"

Setup::Setup() {
  pressedButton = false;
  option = 1;
  level = 1;
  speed = 1;
}
void Setup::print(LiquidCrystal& lcd) {
  switch (option) {
    case 1: {
        lcd.setCursor(0, 0);
        lcd.print(">Level");
        lcd.setCursor(0, 1);
        lcd.print(" Speed");
        lcd.setCursor(7, 1);
        lcd.print(" Back");
        break;
      }
    case 2: {
        lcd.setCursor(0, 0);
        lcd.print(" Level");
        lcd.setCursor(0, 1);
        lcd.print(">Speed");
        lcd.setCursor(7, 1);
        lcd.print(" Back");
        break;
      }
    case 3: {
        lcd.setCursor(0, 0);
        lcd.print(" Level");
        lcd.setCursor(0, 1);
        lcd.print(" Speed");
        lcd.setCursor(7, 1);
        lcd.print(">Back");
        break;
      }
  }
}
void Setup::printWhenButtonPressed(LiquidCrystal& lcd, int& optionMenu, bool& pressed) {
  switch(option) {
    case 1: {
      this->printLevel(lcd);
      break;
    }
    case 2: {
     this->printSpeed(lcd);
     break;
    }
    case 3: {
      lcd.clear();
      pressed = false;
      pressedButton = false;
      optionMenu = 1;
      break;
    }
}
}

void Setup::printLevel(LiquidCrystal& lcd) {
  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.setCursor(0, 1);
  switch(level) {
    case 1: {
      lcd.print("Easy     ");
      break;
    }
    case 2: {
      lcd.print("Medium   ");
      break;
    }
    case 3: {
      lcd.print("Difficult");
      break;
    }
  }
}

void Setup::printSpeed(LiquidCrystal& lcd) {
  lcd.setCursor(0, 0);
  lcd.print("Speed:");
  lcd.setCursor(0, 1);
  switch(speed) {
    case 1: {
      lcd.print("1 m/sec");
      break;
    }
    case 2: {
      lcd.print("2 m/sec");
      break;
    }
    case 3: {
      lcd.print("3 m/sec");
      break;
    }
  }
}
void Setup::modifyLevel(int yValue, bool& joyMoved, int& timeLeft, float& score, int& firstDigit) {
  if (yValue < MIN_THRESHOLD && joyMoved == false) {
    ++level;
    if (level > 3) {
      level = 1; 
    }
    joyMoved = true;
  } 
  if (yValue > MAX_THRESHOLD && joyMoved == false) {
    --level;
    if (level < 1) {
      level = 3;
    }
    joyMoved = true;
  }
  if (yValue > MIN_THRESHOLD && yValue < MAX_THRESHOLD) {
    joyMoved = false;
  }
  switch(level) {
    case 1: {
      firstDigit = 4;
      timeLeft = 240;
      score = 240;
      break;
    }
    case 2: {
      firstDigit = 3;
      timeLeft = 180;
      score = 180 * 1.5;
      break;
    }
    case 3: {
      firstDigit = 2;
      timeLeft = 120;
      score = 120 * 2.5;
      break;
    }
  }
  
}
void Setup::modifySpeed(int yValue, bool& joyMoved, float& menuSpeed) {
  if (yValue < MIN_THRESHOLD && joyMoved == false) {
    ++speed;
    if (speed > 3) {
      speed = 1; 
    }
    joyMoved = true;
  } 
  if (yValue > MAX_THRESHOLD && joyMoved == false) {
    --speed;
    if (speed < 1) {
      speed = 3;
    }
    joyMoved = true;
  }
  if (yValue > MIN_THRESHOLD && yValue < MAX_THRESHOLD) {
    joyMoved = false;
  }
  switch(speed) {
    case 1: {
      menuSpeed = 1;
      break;
    }
    case 2: {
      menuSpeed = 0.75;
      break;
    }
    case 3: {
      menuSpeed = 0.5;
      break;
    }
  }
  
}
void Setup::modifyOption(int xValue, bool& joyMoved) {
  if (xValue < MIN_THRESHOLD && joyMoved == false) {
    ++option;
    if (option > 3) {
      option = 1; 
    }
    joyMoved = true;
  } 
  if (xValue > MAX_THRESHOLD && joyMoved == false) {
    --option;
    if (option < 1) {
      option = 3;
    }
    joyMoved = true;
  }
  if (xValue > MIN_THRESHOLD && xValue < MAX_THRESHOLD) {
    joyMoved = false;
  }
}
