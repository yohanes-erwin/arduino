void setup() 
{
  // Initialize PB5 (LED on digital pin 13 Arduino
  bitSet(DDRB, 5);
  
  Serial.begin(9600);
}

void loop() 
{
  if (Serial.available())
  {
    char c = Serial.read();
    
    if (c == 'H')
    {
      // Turn on LED
      bitSet(PORTB, 5);
    }
    else if (c == 'L')
    {
      // Turn off LED
      bitClear(PORTB, 5);
    }  
  }
}
