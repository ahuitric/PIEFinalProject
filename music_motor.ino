// This code runs the motor that spins the music box gears.
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor = AFMS.getMotor(3);

double speed;
void setup() {
  Serial.begin(9600);
  AFMS.begin();
  motor->run(FORWARD);
  speed = 50;
}

void loop() {
  // run motor
  motor->setSpeed(speed);
}
