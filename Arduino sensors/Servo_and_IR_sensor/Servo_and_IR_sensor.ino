void setup() {
  
  pinMode(7, INPUT);
  

  Serial.begin(9600); // Pour a bowl of Serial

}

void loop() {
   
  ch2 = pulseIn(7, HIGH, 25000); // each channel
  

 

  Serial.print("Channel 2:");
  Serial.println(ch2);

  

  delay(2000 ); // I put this here just to make the terminal 
              // window happier

}
