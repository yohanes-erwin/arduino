void setup()
{
  Serial.begin(9600);
}

void loop()
{
  float millivolts = (analogRead(0)/1024.0) * 5 * 1000;
  int c = round(millivolts / 10);
  int f = round((c*9/5) + 32);
  
  Serial.print(c);
  Serial.write(176);
  Serial.print("C,");
  Serial.print(f);
  Serial.write(176);
  Serial.print("F.");
  
  delay(1000);
}
