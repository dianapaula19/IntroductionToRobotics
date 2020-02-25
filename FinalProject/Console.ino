#include <Ultrasonic.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>
#define CONTRAST 127
#define V0 30
#define RS 32
#define ENABLE 34
#define D4 36
#define D5 38
#define D6 40
#define D7 42
#define DEBOUNCE_DELAY 100
#define TIME 200
#define SEC 1000
LiquidCrystal lcd(RS, ENABLE, D4, D5, D6, D7);


const int buttonStart = 2;
const int buttonClaw = 3;
const int joystickX1 = A1;
const int joystickY1 = A0;
const int joystickY2 = A2;
const int trigSonicCoin = 10;
const int echoSonicCoin = 9;
const int trigSonicPrize = 6;
const int echoSonicPrize = 5;

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0; 
bool gameOver = false;
bool insertedCoin = false;
bool prizeWon = false;
bool pressedStartButton = false;
bool pressedClawButton = false;

unsigned long timeStart = 0;
unsigned long timeInsert = 0;
unsigned long timeWon = 0;
unsigned long timeLost = 0;

// variables for timer
signed short minutes = 3, seconds = 0;
unsigned long second = 0;
char timerText[16];
// variables for the transmitter
const byte address[6] = "00001";
RF24 radio(7, 8); // CE, CSN

Ultrasonic ultrasonicCoin(trigSonicCoin, echoSonicCoin, 6000);
Ultrasonic ultrasonicPrize(trigSonicPrize, echoSonicPrize, 6000);

int xAxis;
int yAxis;
int zAxis;


void pressButton(const int buttonPin, bool &pressedButton) {
  // function to check whether or not a certain button was pressed
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != buttonState) {
      
      buttonState = reading;
      if (buttonState == LOW) {
        pressedButton = true;     
      }
    }
  }
  lastButtonState = reading;

}

void timer() {
  // function to display the time left on the lcd
  lcd.setCursor(0, 0);
  lcd.println("Time:           ");
  lcd.setCursor(0, 1);
  sprintf(timerText, "%0.2d mins %0.2d secs", minutes, seconds);
  lcd.print(timerText);
  if ((millis() - second) > SEC) {
    second = millis();
    seconds--;
    if (seconds == -1) {
      seconds = 59;
      minutes--;
    }
  }
}

void reset() {
  lcd.clear();
  gameOver = false;
  prizeWon = false;
  insertedCoin = false;
  minutes = 3;
  seconds = 0;
}

void setupButtons() {
   pinMode(buttonStart, INPUT_PULLUP);
   pinMode(buttonClaw, INPUT_PULLUP);
}

void setupRadioTransmitter() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void setupJoysticks() {
   pinMode(joystickX1, INPUT);
   pinMode(joystickY1, INPUT);
   pinMode(joystickY2, INPUT);
}

void setupLcd() {
  lcd.begin(16, 2);
  analogWrite(V0, CONTRAST);
}

void setup() {
  setupButtons();
  setupLcd();
  setupJoysticks();
  setupRadioTransmitter(); 
  Serial.begin(9600);
  
  }

struct package {
  int x, y, z;
};

void clawMovement() {
 
  xAxis = analogRead(joystickX1);
  yAxis = analogRead(joystickY1);
  zAxis = analogRead(joystickY2);
  radio.write(&(package){xAxis, yAxis, zAxis},sizeof(package));
  // sends the value of the values of the joysticks in order to control the motors
  pressButton(buttonClaw, pressedClawButton);
  // checks to see if the buttonClaw was pressed and sends either 0 or 1 depending on the answer
  const int on = 1;
  const int off = 0;
  if(pressedClawButton == true) { 
    radio.write(&on, sizeof(on));
  } else {
    radio.write(&off, sizeof(off));
  }
}

void loop() {
  
    if(insertedCoin == false) {
      int distanceCoin = ultrasonicCoin.read();
      lcd.setCursor(0, 0);
      lcd.println("Insert a coin!  ");     
      if(distanceCoin > 0 && distanceCoin < 4) {
        timeInsert = millis();
        insertedCoin = true;
      }
    }else if (insertedCoin == true) {
      if((millis() - timeInsert) < TIME) {
        lcd.clear();
      } else if (pressedStartButton == false) {
        lcd.setCursor(0, 0);
        lcd.println("Press the button");
        lcd.setCursor(0, 1);
        lcd.println("to start!       ");
        pressButton(buttonStart, pressedStartButton);
        timeStart = millis();
      } else if (pressedStartButton == true && prizeWon == false && gameOver == false) {
          if ((millis() - timeStart) < TIME) {
            lcd.clear();
            second = millis();
          } else {
              timer();
              int distancePrize = ultrasonicPrize.read();
              if (distancePrize > 0 && distancePrize < 5) {
                prizeWon = true;
                timeWon = millis();
                lcd.clear();
                }
              if (minutes == -1) {
                lcd.clear();
                gameOver = true;     
                timeLost = millis();   
              }
          }
     }
  }
  
  if (gameOver == true) {
    if ((millis() - timeLost) < 1.5 * SEC) {
      lcd.setCursor(0, 0);
      lcd.println("Awww :( Too bad ");
      lcd.setCursor(0, 1);
      lcd.println("You lost        ");
    } else {
      reset();
    }
  }
  if (prizeWon == true) {
    if ((millis() - timeWon) < 1.5 * SEC) {
      lcd.setCursor(0, 0);
      lcd.println("Yay! You won     ");
      lcd.setCursor(0, 1);
      lcd.println("You are the best!");
    } else {
      reset();
    }
  }
 
}
