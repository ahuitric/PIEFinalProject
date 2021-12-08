#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Adafruit_PWMServoDriver.h>
#include "HCPCA9685.h"
//import adafruit_motor.servo
//from adafruit_servokit import ServoKit
//kit = ServoKit(channels=16)

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
HCPCA9685 HCPCA9685(0x40);
#define MIN_PULSE_WIDTH 125
#define MAX_PULSE_WIDTH 575
#define FREQUENCY 60


// servo = adafruit_motor.servo.Servo(servo_channel)
// kit.servo[0].angle=180
// notes to pins
//Servo note_C4;
//Servo note_D4;
//Servo note_E4;
//Servo note_F4;
//Servo note_G4;
//Servo note_A4;
//Servo note_As4;
//Servo note_B4;
//Servo note_C5;
//Servo note_Cs5;
//Servo note_D5;
//Servo note_Ds5;
//Servo note_E5;
//Servo note_F5;// I skipf#5
//Servo note_G5;
//Servo note_Gs5;
//Servo note_A5;
//Servo note_As5;
//Servo note_B5;
//Servo note_C6;

int note_C4 = 0;
int note_D4 = 1;
int note_E4 = 2;
int note_F4 = 3;
int note_G4 = 4;
int note_A4 = 5;
int note_B4 = 6;
int note_C5 = 7;
int note_D5 = 8;
int note_E5 = 9;
int note_F5 = 10;
int note_G5 = 11;
int note_A5 = 12;
int note_B5 = 13;
int note_C6 = 14;

int WHOLE = 2000;
int HALF = 1000;
int QUARTER = 500;
int EIGHTH = 250;

int state = 1;
int current_emotion = 0;
String incomingmsg; //for incoming serial data
int song_status = 0; // change to 1 while playing then 0 when not

void setup() {
  Serial.begin(115200); // maybe needs to be changed? dont know
  // need to setup connection to serial input from laptop
//  pwm.begin();
//  pwm.setPWMFreq(FREQUENCY);
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  AFMS.begin();
  
//  note_C4.attach(0);
//  note_D4.attach(1);
//  note_E4.attach(2);
//  note_F4.attach(3);
//  note_G4.attach(4);
//  note_A4.attach(5);
//  note_As4.attach(6);
//  note_B4.attach(7);
//  note_C5.attach(8);
//  note_Cs5.attach(9);
//  note_D5.attach(10);
//  note_Ds5.attach(11);
//  note_E5.attach(12);
//  note_F5.attach(13);
//  note_G5.attach(14);
//  note_Gs5.attach(15);
//  note_A5.attach(16);
//  note_As5.attach(17);
//  note_B5.attach(18);
//  note_C6.attach(19);
}

int pulseWidth(int angle){
    int pulse_wide, analog_value;
    pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
    analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
    Serial.println(analog_value);
    return analog_value;
}

void play_note(int note, int note_length){
    Serial.println(note);
    HCPCA9685.Servo(note, 30);
    delay(10);
    HCPCA9685.Servo(note, 0);
    delay(note_length);
}

void play_chord(int note1, int note2, int note_length){
    Serial.println(note1);
    Serial.print(note2);
    HCPCA9685.Servo(note1, 30);
    HCPCA9685.Servo(note2, 30);
    delay(10);
    HCPCA9685.Servo(note1, 0);
    HCPCA9685.Servo(note2, 0);
    delay(note_length);
}



// song methods
void play_neutral(){ //1
  Serial.println("Neutral");
  song_status = 1;


  song_status = 0;
}

void play_happy(){ // 2
  Serial.println("Happy");
  song_status = 1;
  play_note(note_G4, QUARTER);
  play_note(note_E4, QUARTER);
  play_note(note_G4, HALF);
  play_note(note_G4, QUARTER);
  play_note(note_E4, QUARTER);
  play_note(note_G4, HALF);
  play_note(note_A4, QUARTER);
  play_note(note_G4, QUARTER);
  play_note(note_F4, QUARTER);
  play_note(note_E4, QUARTER);
  play_note(note_D4, QUARTER);
  play_note(note_E4, QUARTER);
  play_note(note_F4, QUARTER);
  play_note(note_E4, EIGHTH);
  play_note(note_F4, EIGHTH);
  play_note(note_G4, QUARTER);
  play_note(note_C4, QUARTER);
  play_note(note_C4, QUARTER);
  play_note(note_C4, EIGHTH);
  play_note(note_C4, EIGHTH);
  play_note(note_C4, EIGHTH);
  play_note(note_D4, EIGHTH);
  play_note(note_E4, EIGHTH);
  play_note(note_F4, EIGHTH);
  play_note(note_G4, HALF);
  play_note(note_G4, QUARTER);
  play_note(note_D4, QUARTER);
  play_note(note_D4, QUARTER);
  play_note(note_F4, QUARTER);
  play_note(note_E4, QUARTER);
  play_note(note_D4, QUARTER);
  play_note(note_C4, HALF);

  play_note(note_G5, QUARTER);
  play_note(note_E5, QUARTER);
  play_note(note_G5, HALF);
  play_note(note_G5, QUARTER);
  play_note(note_E5, QUARTER);
  play_note(note_G5, HALF);
  play_note(note_A5, QUARTER);
  play_note(note_G5, QUARTER);
  play_note(note_F5, QUARTER);
  play_note(note_E5, QUARTER);
  play_note(note_D5, QUARTER);
  play_note(note_E5, QUARTER);
  play_note(note_F5, QUARTER);
  play_note(note_E5, EIGHTH);
  play_note(note_F5, EIGHTH);
  play_note(note_G5, QUARTER);
  play_note(note_C5, QUARTER);
  play_note(note_C5, QUARTER);
  play_note(note_C5, EIGHTH);
  play_note(note_C5, EIGHTH);
  play_note(note_C5, EIGHTH);
  play_note(note_D5, EIGHTH);
  play_note(note_E5, EIGHTH);
  play_note(note_F5, EIGHTH);
  play_note(note_G5, HALF);
  play_note(note_G5, QUARTER);
  play_note(note_D5, QUARTER);
  play_note(note_D5, QUARTER);
  play_note(note_F5, QUARTER);
  play_note(note_E5, QUARTER);
  play_note(note_D5, QUARTER);
  play_note(note_C5, HALF);
  song_status = 0;
}

void play_sad(){//2
  Serial.println("Sad");
  song_status = 1;
  
  song_status = 0;
}

void play_angry(){//3
  Serial.println("Angry");
  song_status = 1;

  song_status = 0;
}

void play_fear(){//4
  Serial.println("Fear");
  song_status = 1;

  song_status = 0;
}

void play_surprise(){//5
  Serial.println("Surprise");
  song_status = 1;

  song_status = 0;
}

void play_disgust(){
  Serial.println("Disgust");
  song_status = 1;

  song_status = 0;
}

void play_song(){
  if (incomingmsg.length() > 0 ){
    if (incomingmsg.toInt() == 1) {
      play_neutral();
    }
    else if (incomingmsg.toInt() == 2) {
      play_happy();
    }
    else if (incomingmsg.toInt() == 3) {
      play_sad();
    }
    else if (incomingmsg.toInt() == 4) {
      play_angry();
    }
    else if (incomingmsg.toInt() == 5) {
      play_fear();
    }
    else if (incomingmsg.toInt() == 6) {
      play_surprise();
    }
    else if (incomingmsg.toInt() == 7) {
      play_disgust();
    }
  }
}
void get_state(){
  if (state == 1){
    song_status = 0;
    state = 2;
  } else if (state == 2) {
    if (song_status == 0);
      Serial.write("Seeking");
      state = 1;
  }
}

// state machine down here start state, currently playing state, find new song state, end state?
void loop(){
      get_state();
  switch(state){
    case 1:
    // not currently playing
      delay(1000);
    case 2:
      incomingmsg = Serial.readString();
      play_song();
  }
}
