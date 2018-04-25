
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
  Serial.begin(9600);

  digitalWrite(dir_a, LOW); //zadavame posokata nazad ili napred 
  //digitalWrite(9, LOW);  
ch2 = pulseIn(9, HIGH, 25000); 
  
  Serial.print("Pulses");
  Serial.print("     ");
  Serial.println(ch2);
  Serial.println("Los gehts");

  for (int i=75; i <= 255; i++){
  
    Serial.println(i);
    analogWrite(pwm_a, i);   //Spins the motor on Channel A at full speed
    delay(30);
  }
 }

void loop() {


}
