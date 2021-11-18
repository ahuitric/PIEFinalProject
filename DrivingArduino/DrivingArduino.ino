#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(4);

double l_speed;
double r_speed;
int state = 1;
const int pinIRd = 1;
const int pinIRa = A1;
const int pinIRd_l = 0;
const int pinIRa_l = A0;
const uint8_t LED_RED = 2;
const uint8_t LED_GREEN = 3;
double r_val, l_val;
int turn_delay = 15;
int incomingByte = 0; // for incoming serial data

void get_state(){
  Serial.print(String(l_val));
  Serial.print("\t");
  Serial.print(String(r_val));
  Serial.print("\t");
  Serial.println(String(state));
  String info = String(r_val) + ", " + String(l_val);
  if (Serial.available()>0){
    incomingByte = Serial.parseInt();
    if (incomingByte > 0){
      turn_delay = incomingByte;
    }
  }
  r_val = (analogRead(pinIRa)+analogRead(pinIRa)+analogRead(pinIRa)+analogRead(pinIRa)+analogRead(pinIRa))/5;
  l_val = (analogRead(pinIRa_l)+analogRead(pinIRa_l)+analogRead(pinIRa_l)+analogRead(pinIRa_l)+analogRead(pinIRa_l))/5;    
  if (state == 1){  
    if (r_val > 1001 & l_val < 1010){
      Serial.println("Changing to 3");
      state = 3;
    }
    if (l_val > 1010 & r_val < 1001){
      Serial.println("Changing to 2");
      state = 2;
    }
    if (r_val > 1001 & l_val > 1010) {
      Serial.println("Changing to 4");
      state = 4;
    }
  }
  else {
    Serial.println("Changing to 1");
    state = 1;
  }
}

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  pinMode(pinIRd,INPUT);
  pinMode(pinIRa,INPUT);
  pinMode(pinIRd_l,INPUT);
  pinMode(pinIRa_l,INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
}

void loop() {
  switch(state){
    case 1:
      rightMotor->run(FORWARD);
      leftMotor->run(FORWARD);
      l_speed = 20;
      r_speed = 20;
      rightMotor->setSpeed(r_speed);
      leftMotor->setSpeed(l_speed);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_RED, LOW);
      while (state == 1){
          get_state();
          delay(5);
        }
      break;
     case 2:
     // left
        rightMotor->run(BACKWARD);
        leftMotor->run(FORWARD);
        l_speed = 20;
        r_speed = 40;
        rightMotor->setSpeed(r_speed);
        leftMotor->setSpeed(l_speed);
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_RED, LOW);
      while (state == 2){
          get_state();
          delay(5);
        }
       break;
      case 3:
      // right
        rightMotor->run(FORWARD);
        leftMotor->run(BACKWARD);
        l_speed = 20;
        r_speed = 40;
        rightMotor->setSpeed(r_speed);
        leftMotor->setSpeed(l_speed);
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
      while (state == 3){
          get_state();
          delay(5);
        }
       break;   
      case 4:
      // left and right detected
        rightMotor->run(FORWARD);
        leftMotor->run(FORWARD);
        l_speed = 20;
        r_speed = 20;
        rightMotor->setSpeed(r_speed);
        leftMotor->setSpeed(l_speed);
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, HIGH);
        while (state == 4){
          get_state();
          delay(5);
        }
       break;   
  }
}
