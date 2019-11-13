const int knockSensor = A2;
const int pushButton = 2;
const int buzzerPin = 9;
const int threshold = 100;
const int interval = 5000;
int pushButtonValue = 0;
int knockSensorValue = 0;
unsigned long int lastWrongMillis = 0;
void setup() {
  pinMode(pushButton, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(knockSensor, INPUT);
  Serial.begin(9600);
}

void loop() {
    Serial.println(knockSensorValue);
    if(knockSensorValue < threshold) {
      // Only read the values when they are less than the threshold
      knockSensorValue = analogRead(knockSensor);
      lastWrongMillis = millis();
    }
    if (knockSensorValue >= threshold) {
      Serial.println("Knock");
      if ((millis() - lastWrongMillis) >= interval) {
      Serial.println("Sound");
        tone(buzzerPin, 880, 500);
        pushButtonValue = digitalRead(pushButton);
        if (pushButtonValue == HIGH) {
          // when the button is pressed, stop the buzzer and read the next value
          Serial.println("the button was pressed");
          noTone(buzzerPin);
          knockSensorValue = analogRead(knockSensor); 
        }
      }
    }
}
