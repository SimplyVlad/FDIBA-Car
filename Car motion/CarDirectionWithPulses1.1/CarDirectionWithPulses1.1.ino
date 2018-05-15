#include <Servo.h>

Servo myservo;//servo entity
int pos = 0; //position for servo
int ch3; // servo

void setup() {
  myservo.attach(9);
  pinMode(5, INPUT);
  
  Serial.begin(9600);
}

void loop() {
  ch3 = pulseIn(5, HIGH, 25000);

  Serial.print("Channel 3:");
  Serial.println(ch3);

  if ((ch3 >= 1500) && (ch3 <= 1600)) // the center postion for controller
  {
    Serial.println("between");
    pos = 90;//set servo to center
    myservo.write(pos); // set to pos which is 90
  }else if ((ch3 >= 1100) && (ch3 <= 1490))
  {
    Serial.println("right");
    pos = 180;
    myservo.write(pos); // goes from 180 degrees to 0 degrees
// waits 15ms for the servo to reach the position
  }
  else
  {
  Serial.println("Left");
  (pos = 0); // goes from 0 degrees to 180 degrees
  // in steps of 1 degree
  myservo.write(pos);
  // tell servo to go to position in variable 'pos'
  }
delay(500);
}
