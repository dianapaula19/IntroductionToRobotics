#include "Configuration.h"
#include "Breakout.h"
#include "Menu.h"
#include "LedControl.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);
LedControl lc = LedControl(DIN, CLK, LOAD, 1);
Breakout breakout;
Menu menu;
bool joyMoved = false;
unsigned long lastDebounceTime = 0;
unsigned long wait = 0;
int lastButtonState = HIGH;
int buttonState = HIGH;

void pressButton() {
  int buttonValue = digitalRead(PIN_SW);
  if (buttonValue != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (buttonValue != buttonState) {
      buttonState = buttonValue;
      if (buttonState == LOW) {
        if (menu.option == 2 && menu.pressedButton == true) {
          menu.s.pressedButton = !menu.s.pressedButton;
        } else {
          menu.pressedButton = !menu.pressedButton;
        }
        menu.won = false;
        menu.lost = false;
        menu.wait = millis();
        lc.clearDisplay(0);
        lcd.clear();
      }
    }
  }
  lastButtonState = buttonValue;
}
void reset() {
  menu.startGameBreakout = false;
  menu.timeLeft = 240;
  menu.s.level = 1;
  menu.s.speed = 1;
  menu.score = 240;
  menu.firstDigit = 4;
  menu.secondDigit = 0;
  menu.thirdDigit = 0;
  breakout.resetBricks();
  breakout.p.pos = 3;
  breakout.b.x = 4;
  breakout.b.y = 6;
  EEPROM.write(0, menu.highScore);

}
void menuFunction() {
  pressButton();
  if (menu.pressedButton == true) {
    if (menu.option == 1) {
      if (menu.startBreakout == true) {
        breakout.setup(lc);
      }
      if (menu.startGameBreakout == true) {
        wait = millis();
        breakout.movePaddle(lc);
        breakout.startGame(lc, menu.speed);
      }
      if (breakout.finishedGame() == true) {
        menu.won = true;
      }
      if (menu.timeLeft == 0) {
        menu.lost = true;
      }

      if (menu.won == true) {
        if (menu.highScore < menu.score) {
          menu.highScore = menu.score;
        }
        reset();

        unsigned time = millis() - wait;
        if (time < 300) {
          lcd.clear();
          lc.clearDisplay(0);
        } else if (time > 300 && time < SECOND * 2) {
          lcd.setCursor(0, 0);
          lcd.print("You did it :D");
        } else if (time > SECOND * 2 && time < SECOND * 2 + 300) {
          lcd.clear();
        } else if (time > SECOND * 2 + 300 && time < SECOND * 3) {
          lcd.setCursor(0, 0);
          lcd.print("Press the button");
          lcd.setCursor(0, 1);
          lcd.print("to go back");
        }
      }
      if (menu.lost == true) {
        reset();
        unsigned time = millis() - wait;
        if (time < 300) {
          lcd.clear();
          lc.clearDisplay(0);
        } else if (time > 300 && time < SECOND * 2) {
          lcd.setCursor(0, 0);
          lcd.print("Aww, too bad :(");
        } else if (time > SECOND * 2 && time < SECOND * 2 + 300) {
          lcd.clear();
        } else if (time > SECOND * 2 + 300 && time < SECOND * 3) {
          lcd.setCursor(0, 0);
          lcd.print("Press the button");
          lcd.setCursor(0, 1);
          lcd.print("to go back");
        }
      }

    }

    if (menu.s.pressedButton == true) {
      menu.s.printWhenButtonPressed(lcd, menu.option, menu.pressedButton);
      int yValue = analogRead(PIN_Y);
      switch (menu.s.option) {
        case 1: {
            menu.s.modifyLevel(yValue, joyMoved, menu.timeLeft, menu.score, menu.firstDigit);
            break;
          }
        case 2: {
            menu.s.modifySpeed(yValue, joyMoved, menu.speed);
            break;
          }
      }

    } else {
      int xValue = analogRead(PIN_X);
      menu.printWhenButtonPressed(lcd);
      menu.s.modifyOption(xValue, joyMoved);
    }

  } else {
    int xValue = analogRead(PIN_X);
    menu.print(lcd);
    menu.modifyOption(xValue, joyMoved);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogWrite(V0, CONTRAST);
  pinMode(PIN_SW, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.clear();
  lc.shutdown(0, false);
  lc.setIntensity(0, 2);
  lc.clearDisplay(0);
  float highScore = EEPROM.read(0);
  menu.highScore = highScore;

}

void loop() {
  breakout.millis = millis();
  menu.millis = millis();
  menuFunction();
  Serial.print("lost = ");
  Serial.println(menu.lost);
  Serial.print("startedGame = ");
  Serial.println(menu.startGameBreakout);

  //menuFunction();
  // put your main code here, to run repeatedly:


}
