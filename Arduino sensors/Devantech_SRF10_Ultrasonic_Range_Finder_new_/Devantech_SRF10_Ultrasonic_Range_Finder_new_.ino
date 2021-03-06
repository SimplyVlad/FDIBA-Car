
#define Echo_EingangsPin 7 // Echo input-pin 7
#define Trigger_AusgangsPin 2 // Trigger output-pin 2
 
// Needed variables will be defined and initialized
int maximumRange = 300; 
int minimumRange = 2; 
long Abstand;
long Dauer;
 
void setup() {
 pinMode(Trigger_AusgangsPin, OUTPUT);
 pinMode(Echo_EingangsPin, INPUT);
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
  
 // Check if the measured value is in the permitted range
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
 }
  // Break between single measurements
 delay(500);
}
