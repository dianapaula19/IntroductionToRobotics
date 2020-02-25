#include <AFMotor.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <Servo.h>
#define NEGATIVE -1
#define POSITIVE 1
#define minTHjoystick 300
#define maxTHjoystick 700

const int servoPin = 24;

RF24 radio (46, 48);
const byte address[6] = "00001";

bool clawState = false;

int joyMovedX = false;
int joyMovedY = false;
int joyMovedZ = false;
int xAxis;
int yAxis;
int zAxis;

// the motors used
Servo servo;
AF_DCMotor motorX(1);
AF_DCMotor motorY(3);
AF_DCMotor motorZ1(2);
AF_DCMotor motorZ2(4);

void setupRadio() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void setupServo()
{
  servo.attach(45);
}

void setup() {
  setupRadio();
  Serial.begin(9600);
  motorX.setSpeed(200);
  motorZ1.setSpeed(200);
  motorZ2.setSpeed(200);
  motorY.setSpeed(200);
  motorX.run(RELEASE);
  motorY.run(RELEASE);
  motorZ1.run(RELEASE);
  motorZ2.run(RELEASE);
  setupServo();
}


void moveXY(AF_DCMotor motor, int directions) {
  motor.setSpeed(200);
  if (directions == POSITIVE) {
    motor.run(FORWARD);
  }
  else if (directions == NEGATIVE) {
    motor.run(BACKWARD);
  }
}

void moveZ(int directions) {
  motorZ1.setSpeed(120);
  motorZ2.setSpeed(120);
  if (directions == POSITIVE) {
    motorZ1.run(FORWARD);
    motorZ2.run(BACKWARD);
  } else if (directions == NEGATIVE) {
    motorZ1.run(BACKWARD);
    motorZ2.run(FORWARD);
  }
}

struct package {
  int x, y, z;
} received;

void loop() {

  if (radio.available()) {
    // the motors receive the data from the joysticks
    radio.read(&received, sizeof(package));
    radio.read(&clawState, sizeof(clawState));
    xAxis = received.x;
    yAxis = received.y;
    zAxis = received.z;

    //  movement on X axis
    if (xAxis > maxTHjoystick && joyMovedX == false) {
      moveXY(motorX, NEGATIVE);
      joyMovedX = true;
    }
    if (xAxis < minTHjoystick && joyMovedX == false) {
      moveXY(motorX, POSITIVE);
      joyMovedX = true;
    }
    if (xAxis > minTHjoystick && xAxis < maxTHjoystick) {
      motorX.run(RELEASE);
      joyMovedX = false;
    }

    //  movement on Y axis
    if (yAxis > maxTHjoystick && joyMovedY == false ) {
      moveXY(motorY, NEGATIVE);
      joyMovedY = true;
    }
    if (yAxis < minTHjoystick && joyMovedY == false) {
      moveXY(motorY, POSITIVE);
      joyMovedY = true;
    }
    if (yAxis < maxTHjoystick && yAxis > minTHjoystick) {
      motorY.run(RELEASE);
      joyMovedY = false;

    }
    //  movement on Z axis
    if (zAxis > maxTHjoystick && joyMovedZ == false) {
      // the claw moves downwards
      moveZ(NEGATIVE);
      joyMovedZ = true;
    }
    if (zAxis < minTHjoystick && joyMovedZ == false) {
      // the claw moves upwards
      moveZ(POSITIVE);
      joyMovedZ = true;
    }
    if (zAxis < maxTHjoystick && zAxis > minTHjoystick) {
      motorZ1.run(RELEASE);
      motorZ2.run(RELEASE);
      joyMovedZ = false;
    }
  }
}
