#define Echo_EingangsPin 7 // Echo input-pin
#define Trigger_AusgangsPin 8 // Trigger output-pin
 int pwm_a = 3;
int dir_a = 2;
int maximumRange = 300; 
int minimumRange = 2; 
long Abstand;
long Dauer;
int ch2;
 
void setup() {
  pinMode( pwm_a, OUTPUT ); // PWM
  pinMode( dir_a, OUTPUT ); // Direction
  pinMode(9, INPUT); //Initiates Brake Channel A pin
  pinMode(Trigger_AusgangsPin, OUTPUT);
  pinMode(Echo_EingangsPin, INPUT);
  int motorSpeed = 0;
  Serial.begin (9600);
}
 
void loop() {
 
 // Distance measurement will be started with a 10us long trigger signal
 digitalWrite(Trigger_AusgangsPin, HIGH);
 delayMicroseconds(10); 
 digitalWrite(Trigger_AusgangsPin, LOW);
  
 // Now it will be waited at the echo input till the signal was activated
 // and after that the time will be measured how long it is active 
 Dauer = pulseIn(Echo_EingangsPin, HIGH);
  
 // Now the distance will be calculated with the recorded time
 Abstand = Dauer/58.2;
  
 /* Check if the measured value is in the permitted range*/
 if (Abstand >= maximumRange || Abstand <= minimumRange)
 {
    // An error message will be shown if it's not
      Serial.println("Distance is not in the permitted range");
      Serial.println("-----------------------------------");
 }  
  
 else
 {
    // The calculated distance will be shown at the serial output
      Serial.print("The distance is: ");
      Serial.print(Abstand);
      Serial.println("cm");
      Serial.println("-----------------------------------");
      ch2 = pulseIn(9, HIGH, 25000); 
  Serial.print("Pulses");
  Serial.print("     ");
  Serial.println(ch2);
 }
  // Break between single measurements
 delay(5);
 if(ch2<1000)
 {
  digitalWrite(dir_a, HIGH);
     analogWrite(pwm_a, 0);
  }
 else if (Abstand < 20 && Abstand>0) //stop
  {
     digitalWrite(dir_a, HIGH);
     analogWrite(pwm_a, 0);
  }
  else
  {
    digitalWrite(dir_a, HIGH);
    analogWrite(pwm_a, 155 ) ; 
  }


  delay(50);
}

