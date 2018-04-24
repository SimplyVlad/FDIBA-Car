
// Motor Channel A
// PIN PWM       D3
// PIN Direction D12\
// PIN BRAKE     D9

int pwm_a = 3;
int dir_a = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode( pwm_a, OUTPUT ); // 
  pinMode( dir_a, OUTPUT ); // PWM
  //pinMode(9, OUTPUT); //Initiates Brake Channel A pin
  Serial.begin(9600);

   // put your main code here, to run repeatedly:
  digitalWrite(dir_a, LOW); //Establishes forward direction of Channel A
  //digitalWrite(9, LOW);   //Disengage the Brake for Channel A

  Serial.println("Los gehts");

  for (int i=0; i <= 255; i++){
    Serial.println(i);
    analogWrite(pwm_a, i);   //Spins the motor on Channel A at full speed
    delay(50);
  }
 }

void loop() {


}
