define#
int ch3; // servo

void setup() {
  pinMode(8, INPUT);

  Serial.begin(9600);
}

void loop() {
  ch3 = pulseIn(8, HIGH, 25000);

  Serial.print("Channel 3:");
  Serial.println(ch3);

delay(500);
}
