void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Read ADC0 value and mapping the value from range 0-1023 to 0-255
  int potVal = map(analogRead(0), 0, 1023, 0, 255);
  Serial.println(potVal);
  delay(500);
}
