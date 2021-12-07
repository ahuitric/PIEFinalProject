#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// need to do all servo connection stuff someone help me

// need to setup connection to serial input from laptop also someone help me

// notes to pins
Servo note_C4;
Servo note_D4;
Servo note_E4;
Servo note_F4;
Servo note_G4;
Servo note_A4;
Servo note_As4;
Servo note_B4;
Servo note_C5;
Servo note_Cs5;
Servo note_D5;
Servo note_Ds5;
Servo note_E5;
Servo note_F5;// I skipf#5
Servo note_G5;
Servo note_Gs5;
Servo note_A5;
Servo note_As5;
Servo note_B5;
Servo note_C6;

int WHOLE = 1000;
int HALF = 500;
int QUARTER = 250;
int EIGHTH = 125;

int state = 1;
int current_emotion = 0;
String incomingmsg; //for incoming serial data
int song_status = 0; // change to 1 while playing then 0 when not

void setup() {
  Serial.begin(115200); // maybe needs to be changed? dont know
  // need to setup connection to serial input from laptop
  
  AFMS.begin();
  
  note_C4.attach(0);
  note_D4.attach(1);
  note_E4.attach(2);
  note_F4.attach(3);
  note_G4.attach(4);
  note_A4.attach(5);
  note_As4.attach(6);
  note_B4.attach(7);
  note_C5.attach(8);
  note_Cs5.attach(9);
  note_D5.attach(10);
  note_Ds5.attach(11);
  note_E5.attach(12);
  note_F5.attach(13);
  note_G5.attach(14);
  note_Gs5.attach(15);
  note_A5.attach(16);
  note_As5.attach(17);
  note_B5.attach(18);
  note_C6.attach(19);
}

void play_note(Servo note, int note_length){
    note.write(30);
    delay(100);
    note.write(0);
    delay(note_length);
}


// song methods
void play_neutral(){ //0
  Serial.println("Neutral");
  song_status = 1;
  play_note(note_Ds5,WHOLE);
  play_note(note_Ds5,HALF);
  play_note(note_Ds5,QUARTER);
  delay(2000);
  song_status = 0;
}

void play_happy(){ // 1
  Serial.println("Happy");
  song_status = 1;
  play_note(note_Ds5,HALF);
  play_note(note_Ds5,HALF);
  play_note(note_Ds5,HALF);
  delay(2000);
  song_status = 0;
}

void play_sad(){//2
  Serial.println("Sad");
  song_status = 1;
  play_note(note_Ds5,WHOLE);
  play_note(note_Ds5,WHOLE);
  play_note(note_Ds5,WHOLE);
  delay(2000);
  song_status = 0;
}

void play_angry(){//3
  Serial.println("Angry");
  song_status = 1;
  play_note(note_Ds5,QUARTER);
  play_note(note_Ds5,QUARTER);
  play_note(note_Ds5,QUARTER);
  delay(2000);
  // notes go in here
  song_status = 0;
}

void play_fear(){//4
  Serial.println("Fear");
  song_status = 1;
  play_note(note_Ds5,EIGHTH);
  play_note(note_Ds5,EIGHTH);
  play_note(note_Ds5,QUARTER);
  // notes go in here
  song_status = 0;
}

void play_surprise(){//5
  Serial.println("Surprise");
  song_status = 1;
  play_note(note_Ds5,EIGHTH);
  play_note(note_Ds5,EIGHTH);
  play_note(note_Ds5,QUARTER);
  play_note(note_Ds5,EIGHTH);
  play_note(note_Ds5,EIGHTH);
  play_note(note_Ds5,QUARTER);
  // notes go in here
  song_status = 0;
}

void play_disgust(){
  Serial.println("Disgust");
  song_status = 1;
  play_note(note_Ds5,WHOLE);
  play_note(note_Ds5,EIGHTH);
  play_note(note_Ds5,QUARTER);
  // notes go in here
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
