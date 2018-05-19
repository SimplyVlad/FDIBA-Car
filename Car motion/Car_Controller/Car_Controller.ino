 // Motor Channel A
// PIN PWM       D3
// PIN Direction D12\ i D13 ako imame vtori motor
// PIN BRAKE     D9 \ spirachka

int pwm_a = 3;
int dir_a = 2;
int break_a = 8;
int ch2;

void setup() {

  pinMode( pwm_a, OUTPUT ); // PWM
  pinMode( dir_a, OUTPUT ); // Direction
  pinMode(break_a, OUTPUT); //Initiates Brake Channel A pin

  int motorSpeed = 0;
  Serial.begin(9600);
 }

void loop() {
  ch2 = pulseIn(9, HIGH, 25000); 
  Serial.print("Pulses");
  Serial.print("     ");
  Serial.println(ch2);
  
  if (ch2 > 1499) // forward
  {
     digitalWrite(dir_a, HIGH);
     analogWrite(pwm_a, SpeedForward());
  }
  else if(ch2<1200 && ch2>730)//backwards
  {
    digitalWrite(dir_a,LOW);
    analogWrite(pwm_a, SpeedBackwards());
  }
  else //stop(default position)
  {
    digitalWrite(dir_a,HIGH);
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
