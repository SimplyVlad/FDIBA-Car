int sensorpin = A0;
int sensorpin1 = A1;
int val = 0;
int val1 = 0;
int distance; // variable to store the values from sensor(initially zero)
int distance1;

void setup()
{
  Serial.begin(9600);               // starts the serial monitor
}
 
void loop()
{
  val = analogRead(sensorpin);
  val1 = analogRead(sensorpin1);
  distance = 4800/(val - 20);
  distance1 = 4800/(val1 - 20);
  Serial.println(distance1); // prints the value of the sensor to the serial monitor
  Serial.println(distance);
  Serial.println();
  
  delay(200);                    // wait for this much time before printing next value
}
