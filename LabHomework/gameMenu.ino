#include <LiquidCrystal.h>
const int RS = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;
LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

const int pinSW = 13;
const int pinX = A0;
const int pinY = A1;

const int minThreshold = 400;
const int maxThreshold = 600;

const int interval = 5000;
const int intervalExit = 2000;

int xValue = 0;
int yValue = 0;
int everyFiveSec = 0;
int ok = 0;
int lastButtonState = HIGH;
int buttonState;
int choiceOfThePlayer = 0;
int startingLevelValue = 0;
bool firstTimePressed = false;
bool choseOption = false;
bool joyMoved = false;

unsigned long prevMillis = 0;
unsigned long prevMillisExit = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 100;

void mainMenu(int choiceOfThePlayer) {
  lcd.setCursor(0, 0);
  if (choiceOfThePlayer == 0) {
    lcd.print(">Start");
  } else {
    lcd.print(" Start");
  }
  lcd.setCursor(7, 0);
  if (choiceOfThePlayer == 1) {
    lcd.print(">Setup");
  } else {
    lcd.print(" Setup");
  }
  lcd.setCursor(0, 1);
  if (choiceOfThePlayer == 2) {
    lcd.print(">Highscore");
  } else {
    lcd.print(" Highscore");
  }
}
void lcdClearLine(int line) {
  lcd.setCursor(0, line);
  for (int i = 0; i < 16; ++i) {
    lcd.write(' ');
  }
}
void setChoseOptionState() {
  int buttonValue = digitalRead(pinSW);
  if (buttonValue != lastButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonValue != buttonState) {
      buttonState = buttonValue;
      if (buttonState == LOW) {
        choseOption = !choseOption;
        ok = 0;
        everyFiveSec = 0;
        prevMillis = millis();
        lcd.clear();
      }
    }
  }
  lastButtonState = buttonValue;

}
void startMenu() {
  lcd.setCursor(0, 0);
  lcd.print("Lives:3");
  lcd.setCursor(8, 0);
  lcd.print("Level:");
  lcd.setCursor(14, 0);
  lcd.print(startingLevelValue);
  lcd.setCursor(0, 1);
  lcd.print("Score:");
  lcd.setCursor(6, 1);
  lcd.print(startingLevelValue * 3);
}

void exitMenuCongrats() {
  lcd.setCursor(0, 0);
  lcd.print("congrats :D");
}
void exitMenu() {
  if ((millis() - prevMillisExit) > intervalExit) {
    lcdClearLine(0);
    lcd.setCursor(0, 0);
    lcd.print("press the button");
    lcdClearLine(1);
    lcd.setCursor(0, 1);
    lcd.print("to exit");
    prevMillisExit = millis();
  }
}

void setupMenu() {
  lcd.setCursor(0, 0);
  lcd.print("Starting level:");
  lcd.setCursor(0, 1);
  lcd.print(startingLevelValue);
}

void highscoreMenu() {
  lcd.setCursor(0, 0);
  lcd.print("Highscore is:");
  lcd.setCursor(0, 1);
  lcd.print(startingLevelValue * 3);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (choseOption == false) {
    xValue = analogRead(pinX);
    if (xValue > maxThreshold && joyMoved == false) {
      ++choiceOfThePlayer;
      if (choiceOfThePlayer == 3) {
        choiceOfThePlayer = 0;
      }
      joyMoved = true;
    }
    if (xValue < minThreshold && joyMoved == false) {
      --choiceOfThePlayer;
      if (choiceOfThePlayer == -1) {
        choiceOfThePlayer = 2;
      }
      joyMoved = true;
    }
    if (xValue > minThreshold && xValue < maxThreshold) {
      joyMoved = false;
    }
    mainMenu(choiceOfThePlayer);
    setChoseOptionState();

  } else {
    if (choiceOfThePlayer == 0) {
      if (everyFiveSec < 2) {
        startMenu();
        unsigned long currentMillis = millis();
        if ((currentMillis - prevMillis) > interval) {
          ++startingLevelValue;
          if (startingLevelValue == 10) {
            startingLevelValue = 9;
          }
          ++everyFiveSec;
          prevMillis = currentMillis;
        }
      }
      if (everyFiveSec >= 2) {
        if (ok == 0) {
          lcd.clear();
          prevMillisExit = millis();
          exitMenuCongrats();
          ok = 1;
        }
        exitMenu();
        setChoseOptionState();
      }
    }
    if (choiceOfThePlayer == 1) {
      if (ok == 0) {
        lcd.clear();
        ok = 1;
      }
      yValue = analogRead(pinY);
      if (yValue > maxThreshold && joyMoved == false) {
        ++startingLevelValue;
        if (startingLevelValue == 10) {
          startingLevelValue = 0;
        }

        joyMoved = true;
      }
      if (yValue < minThreshold && joyMoved == false) {
        --startingLevelValue;
        if (startingLevelValue == -1) {
          startingLevelValue = 9;
        }
        joyMoved = true;
      }
      if (yValue > minThreshold && yValue < maxThreshold) {
        joyMoved = false;
      }
      setupMenu();
      setChoseOptionState();
    }
    if (choiceOfThePlayer == 2) {
      if (ok == 0) {
        lcd.clear();
        ok = 1;
      }
      highscoreMenu();
      setChoseOptionState();
    }
  }
}
