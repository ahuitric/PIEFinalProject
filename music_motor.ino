#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor = AFMS.getMotor(3);

double speed;
int turn_delay = 15;
void setup() {
  Serial.begin(9600);
  AFMS.begin();
  motor->run(FORWARD);
  speed = 20;
}

void loop() {
  // put your main code here, to run repeatedly:
  motor->setSpeed(speed);
}
