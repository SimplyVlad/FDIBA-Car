
#include <Servo.h> // for servo in example

Servo myservo;//servo entity

int del = 50;
int ch2; // motors

const int channel_a_enable = 6;
const int channel_a_input_1 = 4;
const int channel_a_input_2 = 7;
const int channel_b_enable = 5;
const int channel_b_input_3 = 3;
const int channel_b_input_4 = 2;

int motorSpeedA = 0;
int motorSpeedB = 0;

void setup() {

  pinMode( channel_a_enable, OUTPUT ); // Channel A enable
  pinMode( channel_a_input_1, OUTPUT ); // Channel A input 1
  pinMode( channel_a_input_2, OUTPUT ); // Channel A input 2
  
  pinMode( channel_b_enable, OUTPUT ); // Channel B enable
  pinMode( channel_b_input_3, OUTPUT ); // Channel B input 3
  pinMode( channel_b_input_4, OUTPUT ); // Channel B input 4
  
  myservo.attach(11);
  
  pinMode(9, INPUT);
  
  Serial.begin(9600); // Pour a bowl of Serial

}

void loop() {

  ch2 = pulseIn(9, HIGH, 25000); 
  
  
  Serial.print("Pulses");
  Serial.print("     ");
  Serial.println(ch2);
  
  // motor
  if (ch2 > 1600){ // MOTOR FORWARD
    digitalWrite( channel_a_input_1, LOW);  

    digitalWrite( channel_a_input_2, HIGH);

    digitalWrite( channel_b_input_3, LOW);
    digitalWrite( channel_b_input_4, HIGH);

    motorSpeedA = map(ch2, 1600, 2100, 0, 255);
    motorSpeedB = map(ch2, 1600, 2100, 0, 255);
    
    delay(del);
    
  }else if(ch2<1400) {   // MOTOR BACKWARDS near 900
    
    digitalWrite( channel_a_input_1, HIGH);
    digitalWrite( channel_a_input_2, LOW);
    
    digitalWrite( channel_b_input_3, HIGH);
    digitalWrite( channel_b_input_4, LOW);

    motorSpeedA = map(ch2, 1400, 900, 0, 255);
    motorSpeedB = map(ch2, 1400, 900, 0, 255);
    
    delay(del);
    
  }else{  // MOTOR OFF (default)
              
    motorSpeedA = 0;
    motorSpeedB = 0;
    
    delay(del); 
  }

  analogWrite(channel_a_enable, motorSpeedA); 
  analogWrite(channel_b_enable, motorSpeedB);
  delay(del);

}

