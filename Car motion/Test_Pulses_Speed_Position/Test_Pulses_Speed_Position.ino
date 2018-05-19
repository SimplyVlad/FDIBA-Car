 // Motor Channel A
// PIN PWM       D3
// PIN Direction D12\ i D13 ako imame vtori motor
// PIN BRAKE     D9 \ spirachka
#include <AFMotor.h>            // Addvam foldera v koito sedi Servo.h
#include <Servo.h>              // Add library

Servo name_servo;               // Define any servo name 

int pwm_a = 3;
int dir_a = 2;
int break_a = 8;

int ch1;
int ch2;
int servo_position = 0 ;
int motorSpeed = 0;

void setup() {

  name_servo.attach (11);          // Define the servo signal pins// trqbva da vidq kyde e attachnato(vij saita)

  pinMode( pwm_a, OUTPUT ); // PWM
  pinMode( dir_a, OUTPUT ); // Direction
  pinMode(break_a, OUTPUT); //Initiates Brake Channel A pin
  pinMode(10, INPUT);
  
  Serial.begin(9600);
 }

void loop() {
  ch1 = pulseIn(10, HIGH, 25000);
  ch2 = pulseIn(9, HIGH, 25000);
  Serial.println("Position         Speed");
  Serial.print(ch1);
  Serial.print("          ");
  Serial.println(ch2);
  
 
  for (servo_position = 20; servo_position <=120; servo_position +=1){ // proba za vyrteneto

    name_servo.write(servo_position);
    delay(10);
  }
  digitalWrite(dir_a, HIGH);
  analogWrite(pwm_a, 100);
  delay(2000);
  for (servo_position=120; servo_position >= 20; servo_position -=1){

    name_servo.write(servo_position);
    delay(10);
  }                                                                     //proba za vyrteneto
  digitalWrite(dir_a, HIGH);
  analogWrite(pwm_a, 100);
  delay(2000);
  name_servo.write(90);
  
  if (ch2 > 1499) // forward
  {
     digitalWrite(dir_a, HIGH);
     analogWrite(pwm_a, SpeedForward());
  }
  else if(ch2<1200 && ch2>0)//backwards
  {
    digitalWrite(dir_a,LOW);
    analogWrite(pwm_a, SpeedBackwards());
  }
  else //stop(default position)
  {
    digitalWrite(dir_a,LOW);
    analogWrite(pwm_a, 20);
    digitalWrite(break_a,HIGH);
  }
  delay(50);
}

int SpeedForward()
{
  int motorSpeed = map(ch2, 1300, 1950, 80, 255); 
  return motorSpeed;
}

int SpeedBackwards()
{
  int motorSpeed = map(ch2, 1200, 730, 80 , 255);
  return motorSpeed;
}
