// Motor Channel A
// PIN PWM       D3
// PIN Direction D12\
// PIN BRAKE     D9

#define Echo_EingangsPin 7 // Echo input-pin
#define Trigger_AusgangsPin 8 // Trigger output-pin

int pwm_a = 3;
int dir_a = 2;
long Abstand;
long Dauer;

void setup() {

  pinMode( pwm_a, OUTPUT ); // PWM (speed)
  pinMode( dir_a, OUTPUT ); // Direction (forward/backwards)
  pinMode(9, INPUT); //Initiates Brake Channel A pin
  
  int motorSpeed = 0;
  
  Serial.begin(9600);
 }

void loop() {
  
  Dauer = pulseIn(Echo_EingangsPin, HIGH);
  Abstand = Dauer/58.2;
  
  Serial.print("The distance is: ");
  Serial.print(Abstand);
  Serial.println("cm");
  
  if (Abstand < 10) // 10cm from an object
  {
     digitalWrite(dir_a, HIGH);
     analogWrite(pwm_a, 0);
  }
  else if(Abstand >= 10 && Abstand < 120) // increasing the speed towards the distance
  {
    digitalWrite(dir_a, HIGH);
    analogWrite(pwm_a, SpeedForward()) ; 
  }
  else
  {
    digitalWrite(dir_a, HIGH);
    analogWrite(pwm_a, 151) ; // maximum speed when above 120 cm
  }

  delay(50);
}

int SpeedForward()
{
  int motorSpeed = map(Abstand, 10, 120, 80, 150); 
  return motorSpeed;
}

/*
int SpeedBackwards()
{
  int motorSpeed = map(ch2, 1200, 730, 80 , 255);
  return motorSpeed;
}
*/
