// Motor Channel A
// PIN PWM       D3
// PIN Direction D12\
// PIN BRAKE     D9

int pwm_a = 3;
int dir_a = 2;
int ch2;

void setup() {

  pinMode( pwm_a, OUTPUT ); // PWM
  pinMode( dir_a, OUTPUT ); // Direction
  pinMode(9, INPUT); //Initiates Brake Channel A pin

  int motorSpeed = 0;
  /*
    digitalWrite(dir_a, LOW); //zadavame posokata nazad ili napred 
    digitalWrite(9, LOW);  
   
    for (int i=100; i <= 255; i)
    {
      Serial.println(i);
      analogWrite(pwm_a, i);   //Spins the motor on Channel A at full speed
      delay(30);
    }
  */
  Serial.begin(9600);
 }

void loop() {
  ch2 = pulseIn(9, HIGH, 25000); 
  Serial.print("Pulses");
  Serial.print("     ");
  Serial.println(ch2);
  
  if (ch2 > 1300) // forward
  {
     digitalWrite(dir_a, HIGH);
     analogWrite(pwm_a, SpeedForward());
  }
  else if(ch2<1200)//backwards
  {
    digitalWrite(dir_a,LOW);
    analogWrite(pwm_a, SpeedBackwards());
  }
  else //stop(default position)
  {
    digitalWrite(dir_a,LOW);
    analogWrite(pwm_a, 0);
  }
  delay(50);
}

int SpeedForward()
{
  int motorSpeed = map(ch2, 1300, 1900, 0, 255);
  return motorSpeed;
}

int SpeedBackwards()
{
  int motorSpeed = map(ch2, 1200, 800, 0, 255);
  return motorSpeed;
}
