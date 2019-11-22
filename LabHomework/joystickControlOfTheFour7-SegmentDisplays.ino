// pins for the 4 7-segment display
const int pinDP = 13;
const int pinD4 = 12;
const int pinD3 = 11;
const int pinD2 = 10;
const int pinD1 = 9;
const int pinA = 8;
const int pinB = 7;
const int pinC = 6;
const int pinD = 5;
const int pinE = 4;
const int pinF = 3;
const int pinG = 2;
// pins for the joystick
const int pinSW = A2;
const int pinX = A1;
const int pinY = A0;

const int segSize = 8;

const int noOfDisplays = 4;
const int noOfDigits = 10;

int segments[segSize] = {
pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
// digits array, to switch between them easily
int digits[noOfDisplays] = {
pinD1, pinD2, pinD3, pinD4
};
byte digitMatrix[noOfDigits][segSize - 1] = {
// a b c d e f g
{1, 1, 1, 1, 1, 1, 0}, // 0
{0, 1, 1, 0, 0, 0, 0}, // 1
{1, 1, 0, 1, 1, 0, 1}, // 2
{1, 1, 1, 1, 0, 0, 1}, // 3
{0, 1, 1, 0, 0, 1, 1}, // 4
{1, 0, 1, 1, 0, 1, 1}, // 5
{1, 0, 1, 1, 1, 1, 1}, // 6
{1, 1, 1, 0, 0, 0, 0}, // 7
{1, 1, 1, 1, 1, 1, 1}, // 8
{1, 1, 1, 1, 0, 1, 1} // 9
};
int switchValue;
int minThreshold = 400;
int maxThreshold = 600;
int xValue = 500;
int yValue = 0;
bool readFromX = true;
bool joyMoved = false;
bool pressedTheButton = false;
int digit = 0;
int numberOfTheDisplay = 1;
int lastButtonState = HIGH;
int buttonState;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
void displayNumber(byte digit) {
  for(int i = 0; i < segSize - 1; ++i) {
    digitalWrite(segments[i], digitMatrix[digit][i]);
  }
}
void showDigit(int numberOfTheDisplay) {
  for(int i = 0; i < noOfDisplays; ++i) {
    digitalWrite(digits[i], HIGH);
  }
  digitalWrite(digits[numberOfTheDisplay - 1], LOW);
  displayNumber(0);
}
void setup() {
  // put your setup code here, to run once:
  pinMode(pinSW, INPUT_PULLUP);
  for(int i = 0; i < segSize; ++i) {
    pinMode(segments[i], OUTPUT);
  }
  for(int i = 0; i < noOfDisplays; ++i) {
    pinMode(digits[i], OUTPUT);
  }
  showDigit(numberOfTheDisplay);
  Serial.begin(9600);
}

void loop() {

  if(readFromX == true) {
    xValue = analogRead(pinX);
    Serial.print("xValue = ");
    Serial.println(xValue);
    if(xValue < minThreshold && joyMoved == false) {
      if (numberOfTheDisplay < 4) {
        numberOfTheDisplay++;
      } else {
        numberOfTheDisplay = 1;
      }
      joyMoved = true;
    }
    if(xValue > maxThreshold && joyMoved == false) {
      if (numberOfTheDisplay > 1) {
        numberOfTheDisplay--;
      } else {
        numberOfTheDisplay = 4;
      }
      joyMoved = true;
    }
    if(xValue >= minThreshold && xValue <= maxThreshold) {
      joyMoved = false;
    }
    showDigit(numberOfTheDisplay);
    int reading = digitalRead(pinSW);
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
      Serial.println(buttonState);
      if (reading != buttonState) {
        buttonState = reading;
      }
      if(buttonState == LOW) {
      Serial.println(buttonState);
      readFromX = false;
      joyMoved = false;
      digitalWrite(pinDP, HIGH);
      }
      }
      lastButtonState = reading;
  } else {
    yValue = analogRead(pinY);
    Serial.print("yValue = ");
    Serial.println(yValue);
    if(yValue < minThreshold && joyMoved == false) {
      if (digit < 9) {
        digit++;
      } else {
        digit = 0;
      }
      joyMoved = true;
    }
    if(yValue > maxThreshold && joyMoved == false) {
      if (digit > 0) {
        digit--;
      } else {
        digit = 9;
      }
      joyMoved = true;
    }
    if(yValue >= minThreshold && yValue <= maxThreshold) {
      joyMoved = false;
    }
    displayNumber(digit);
    int reading = digitalRead(pinSW);
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay) {
      Serial.println(buttonState);
      if (reading != buttonState) {
        buttonState = reading;
      }
    if(buttonState == LOW) {
      Serial.println(buttonState);
      readFromX = true;
      joyMoved = false;
      digitalWrite(pinDP, LOW);
      }
      }
      lastButtonState = reading;
  }
  
  // put your main code here, to run repeatedly:
}
