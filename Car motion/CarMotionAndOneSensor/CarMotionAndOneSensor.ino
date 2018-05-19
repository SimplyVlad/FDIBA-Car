// Motor Channel A
// PIN PWM       D3
// PIN Direction D12\
// PIN BRAKE     D9
#include <AFMotor.h>            // Addvam foldera v koito sedi Servo.h
#include <Servo.h>              // Add library

#define Echo_EingangsPin 7      // Echo input-pin
#define Trigger_AusgangsPin 8   // Trigger output-pin

Servo name_servo;

int servo_position = 0 ;
int motorSpeed = 0;

int pwm_a = 3;
int dir_a = 2;
int break_a = 8;

long Abstand;
long Dauer;

void setup() {
  name_servo.attach (11);
  pinMode( pwm_a, OUTPUT );             // PWM (speed)
  pinMode( dir_a, OUTPUT );             // Direction (forward/backwards)
  pinMode(break_a, OUTPUT);             //Initiates Brake Channel A pin
  pinMode(Trigger_AusgangsPin, OUTPUT);
  pinMode(Echo_EingangsPin, INPUT);
  
  Serial.begin(9600);
 }

void loop() {
  digitalWrite(Trigger_AusgangsPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(Trigger_AusgangsPin, LOW);
  Dauer = pulseIn(Echo_EingangsPin, HIGH);
  Abstand = Dauer/58.2;
  
  Serial.print("The distance is: ");
  Serial.print(Abstand);
  Serial.println("cm");
  
  if (Abstand < 35)                         // 10cm from an object
  {
     digitalWrite(dir_a, HIGH);
     analogWrite(pwm_a, 70);
     digitalWrite(break_a,HIGH); 
  }
  else if(Abstand >= 35 && Abstand < 120)   // increasing the speed towards the distance
  {
    digitalWrite(dir_a, LOW);
    analogWrite(pwm_a, SpeedForward()) ; 
  }
  else
  {
    digitalWrite(dir_a, LOW);
    analogWrite(pwm_a, 150) ;               // maximum speed when above 120 cm
  }

  delay(50);
}

int SpeedForward()
{
  int motorSpeed = map(Abstand, 35, 200, 80, 145); 
  return motorSpeed;
}

/*
int SpeedBackwards()
{
  int motorSpeed = map(ch2, 1200, 730, 80 , 255);
  return motorSpeed;
}
*/
