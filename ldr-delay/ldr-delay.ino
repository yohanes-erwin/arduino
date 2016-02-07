void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{
  int ldrVal = analogRead(0); 
  ldrVal = map(ldrVal, 200, 1000, 100, 1000);
  ldrVal = constrain(ldrVal, 100, 1000);
  
  // Toggle LED with delay variation (100ms - 1000ms)
  digitalWrite(13, HIGH);
  delay(ldrVal);
  digitalWrite(13, LOW);
  delay(ldrVal);
}
  

