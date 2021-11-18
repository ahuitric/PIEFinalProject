#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  
}
void loop() {
  servo1.write(15);
  servo2.write(15);
  servo3.write(15);
  delay(100);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  delay(100);
  //delay(2000);
  servo1.write(15);
  servo2.write(15);
  servo3.write(15);
  delay(500);
  //delay(2000);
  servo1.write(30);
  servo2.write(30);
  servo3.write(30);
  delay(100);
  //delay(2000);
  servo1.write(15);
  servo2.write(15);
  servo3.write(15);
  delay(500);
  //delay(2000);
}
