#include "Menu.h"
#include <LiquidCrystal.h>

Menu::Menu() {
  option = 1;
  score = 300;
  speed = 1;
  timeLeft = 300;
  firstDigit = 5;
  secondDigit = 0;
  thirdDigit = 0;
  startBreakout = false;
  startGameBreakout = false;
  stopBreakout = false;
  pressedButton = false;
  wait = 0;
  waitDisplay = 0;
  waitDigits = 0;
}
void Menu::print(LiquidCrystal& lcd) {
  switch (option) {
    case 1: {
        lcd.setCursor(0, 0);
        lcd.print(">Start");
        lcd.setCursor(7, 0);
        lcd.print(" Setup");
        lcd.setCursor(0, 1);
        lcd.print(" HighScore");
        lcd.setCursor(11, 1);
        lcd.print(" Info");
        break;
      }
    case 2: {
        lcd.setCursor(0, 0);
        lcd.print(" Start");
        lcd.setCursor(7, 0);
        lcd.print(">Setup");
        lcd.setCursor(0, 1);
        lcd.print(" HighScore");
        lcd.setCursor(11, 1);
        lcd.print(" Info");
        break;
      }
    case 3: {
        lcd.setCursor(0, 0);
        lcd.print(" Start");
        lcd.setCursor(7, 0);
        lcd.print(" Setup");
        lcd.setCursor(0, 1);
        lcd.print(">HighScore");
        lcd.setCursor(11, 1);
        lcd.print(" Info");
        break;
      }
    case 4: {
        lcd.setCursor(0, 0);
        lcd.print(" Start");
        lcd.setCursor(7, 0);
        lcd.print(" Setup");
        lcd.setCursor(0, 1);
        lcd.print(" HighScore");
        lcd.setCursor(11, 1);
        lcd.print(">Info");
        break;
      }
  }
}
void Menu::printStart(LiquidCrystal& lcd) {
  unsigned long time = millis - wait;
  if (time < INTERVAL_START) {
    lcd.setCursor(0, 0);
    lcd.print(" AkiraBreakout ");
    lcd.setCursor(0, 1);
    lcd.print("****THE GAME****");
  } else if (time > INTERVAL_START && time < INTERVAL_START + 200) {
    lcd.clear();
    waitDigits = millis;
    startBreakout = true;
  } else if (time > INTERVAL_START + 200 && timeLeft > -1 && won == false && lost == false) {
    startBreakout = false;
    startGameBreakout = true;
    lcd.setCursor(0, 0);
    lcd.print("Time Left: ");
    lcd.setCursor(11, 0);
    lcd.print(firstDigit);
    lcd.setCursor(12, 0);
    lcd.print(":");
    lcd.setCursor(13, 0);
    lcd.print(secondDigit);
    lcd.setCursor(14, 0);
    lcd.print(thirdDigit);
    lcd.setCursor(0, 1);
    lcd.print("Score: ");
    lcd.setCursor(7, 1);
    if (score > 99) {
      lcd.print(score);
      lcd.setCursor(10, 1);
      lcd.print(".");
    } else if (score > 9) {
      lcd.print(score);
      lcd.setCursor(9, 1);
      lcd.print(".");
      lcd.setCursor(12, 1);
      lcd.print(" ");
    } else {
      lcd.print(score);
      lcd.setCursor(8, 1);
      lcd.print(".");
      lcd.setCursor(11, 1);
      lcd.print("  ");
    }
    this->changeTime();
  }
}

void Menu::printHighScore(LiquidCrystal& lcd) {
  lcd.setCursor(0, 0);
  lcd.print("HighScore:");
  lcd.setCursor(0, 1);
  if (highScore > 99) {
      lcd.print(highScore);
      lcd.setCursor(3, 1);
      lcd.print(".");
    } else if (highScore > 9) {
      lcd.print(highScore);
      lcd.setCursor(2, 1);
      lcd.print(".");
      lcd.setCursor(5, 1);
      lcd.print(" ");
    } else {
      lcd.print(highScore);
      lcd.setCursor(1, 1);
      lcd.print(".");
      lcd.setCursor(4, 1);
      lcd.print("  ");
    }

}
void Menu::printInfo(LiquidCrystal& lcd) {
  if ((millis - wait) < INTERVAL_INFO) {
    lcd.setCursor(0, 0);
    lcd.print("Name:");
    lcd.setCursor(0, 1);
    lcd.print("Diana B.");
  } else if ( (millis - wait) < INTERVAL_INFO + 200) {
    lcd.clear();
  } else if ((millis - wait) < INTERVAL_INFO * 2) {
    lcd.setCursor(0, 0);
    lcd.print("Github:");
    lcd.setCursor(0, 1);
    lcd.print("@dianapaula19");
  } else if ((millis - wait) < INTERVAL_INFO * 2 + 200) {
    lcd.clear();
  } else if ((millis - wait) < INTERVAL_INFO * 3) {
    lcd.setCursor(0, 0);
    lcd.print("@UnibucRobotics");
    lcd.setCursor(0, 1);
  } else {
    lcd.clear();
    pressedButton = false;
  }
}
void Menu::printWhenButtonPressed(LiquidCrystal& lcd) {
  switch (option) {
    case 1: {
        this->printStart(lcd);
        break;
      }
    case 2: {
        s.print(lcd);
        break;
      }
    case 3: {
        this->printHighScore(lcd);
        break;
      }
    case 4: {
        this->printInfo(lcd);
        break;
      }

  }
}
void Menu::modifyOption(int xValue, bool& joyMoved) {
  if (xValue < MIN_THRESHOLD && joyMoved == false) {
    ++option;
    if (option > 4) {
      option = 1;
    }
    joyMoved = true;
  }
  if (xValue > MAX_THRESHOLD && joyMoved == false) {
    --option;
    if (option < 1) {
      option = 4;
    }
    joyMoved = true;
  }
  if (xValue > MIN_THRESHOLD && xValue < MAX_THRESHOLD) {
    joyMoved = false;
  }
}
void Menu::changeTime() {
  unsigned long time = millis - waitDigits;
  if (time > SECOND && timeLeft > 0) {
    --timeLeft;
    switch (s.level) {
      case 1: {
          score -= 1;
          break;
        }
      case 2: {
          score -= 1.5;
          break;
        }
      case 3: {
          score -= 2.5;
          break;
        }
    }
    if (secondDigit == 0 && thirdDigit == 0) {
      --firstDigit;
      secondDigit = 5;
      thirdDigit = 10;
    }
    if (thirdDigit == 0) {
      --secondDigit;
      thirdDigit = 10;
    }
    --thirdDigit;
    waitDigits = millis;
  }
}
