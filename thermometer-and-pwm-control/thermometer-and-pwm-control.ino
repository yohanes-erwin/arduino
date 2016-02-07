int outputValue;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Get ADC value, covert to celcius and fahrenheit
  float millivolts = (analogRead(0)/1024.0) * 5 * 1000;
  int c = round(millivolts / 10);
  int f = round((c*9/5) + 32);
  
  // Set PWM value based on celcius value
  if (c < 24)
    outputValue = 0;
  else if ((c >= 24) && (c <= 30))
    outputValue = map(c, 24, 30, 64, 255);
  else if (c > 30)
    outputValue = 255;
  
  // Output PWM value  
  analogWrite(9, outputValue);
  // Scale PWM value from range 0-255 to 0-100
  int outputPercentage = map(outputValue, 0, 255, 0, 100); 
  
  Serial.print(c);
  Serial.write(176);
  Serial.print("C,");
  Serial.print(f);
  Serial.write(176);
  Serial.print("F,");
  Serial.print(outputPercentage);
  Serial.print("%.");
  
  delay(1000);
}
