#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// need to do all servo connection stuff someone help me

// need to setup connection to serial input from laptop also someone help me

// notes to pins
Servo C4;
Servo D4;
Servo E4;
Servo F4;
Servo G4;
Servo A4;
Servo As4;
Servo B4;
Servo C5;
Servo Cs5;
Servo D5;
Servo Ds5;
Servo E5;
Servo F5;// I skipf#5
Servo G5;
Servo Gs5;
Servo A5;
Servo As5;
Servo B5;
Servo C6;

int C4_pos = 0;
int D4_pos = 0;
int E4_pos = 0;
int F4_pos = 0;
int G4_pos = 0;
int A4_pos = 0;
int As4_pos = 0;
int B4_pos = 0;
int C5_pos = 0;
int Cs5_pos = 0;
int D5_pos = 0;
int Ds5_pos = 0;
int E5_pos = 0;
int F5_pos = 0;
int G5_pos = 0;
int Gs5_pos = 0;
int A5_pos = 0;
int As5_pos = 0;
int B5_pos = 0;
int C6_pos = 0;

int WHOLE = 1000;
int HALF = 500;
int QUARTER = 250;
int EIGHTH = 125;

int state = 1;
int current_emotion = 0;
int incomingByte = 0; //for incoming serial data
int song_status = 0; // change to 1 while playing then 0 when not

void setup() {
  Serial.begin(9600); // maybe needs to be changed? dont know
  // need to setup connection to serial input from laptop
  AFMS.begin();
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  C4.attach(0);
  D4.attach(1);
  E4.attach(2);
  F4.attach(3);
  G4.attach(4);
  A4.attach(5);
  As4.attach(6);
  B4.attach(7);
  C5.attach(8);
  Cs5.attach(9);
  D5.attach(10);
  Ds5.attach(11);
  E5.attach(12);
  F5.attach(13);
  G5.attach(14);
  Gs5.attach(15);
  A5.attach(16);
  As5.attach(17);
  B5.attach(18);
  C6.attach(19);
}

void play_note(note,note_pos, note_length){
  if (note_pos < 90){ // needs to be changed
    note.write(90);
    delay(note_length);
  }
  else {
    note.write(0);
    delay(note_length);
  }
}

// song methods
void play_neutral(){ //0
}

void play_happy(){ // 1
}

void play_sad(){//2
}

void play_angry(){//3
}

void play_fear(){//4
}

void play_surprise(){//5
}

void get_state(){
  if (state == 1)
}

// state machine down here start state, currently playing state, find new song state, end state?
void loop(){
  switch(state){
    case 1:
    // not currently playing
    // read serial input from laptop
    // change current emotion to mach the output
    
    case 2:
    case 3:
  }
}
}
