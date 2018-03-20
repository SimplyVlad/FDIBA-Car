int sensorpin = A0;                 // analog pin used to connect the sharp sensor
int val = 0;
int distance; // variable to store the values from sensor(initially zero)

void setup()
{
  Serial.begin(9600);               // starts the serial monitor
}
 
void loop()
{
  val = analogRead(sensorpin);       // reads the value of the sharp sensor
  distance = 4800/(val - 20);
  Serial.println(distance);
  Serial.println(" cm"); // prints the value of the sensor to the serial monitor
  
  delay(100);                    // wait for this much time before printing next value
}
