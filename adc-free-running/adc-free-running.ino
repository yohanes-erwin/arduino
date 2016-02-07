void setup()
{
  // Initialize ADC
  adc0_init();
  Serial.begin(9600);
}

void loop()
{
  // Get celcius value from ADC
  float millivolts = (ADC/1024.0) * 5 * 1000;
  float celsius = millivolts / 10;
  
  // Print to serial monitor
  Serial.print("Temp = ");
  Serial.print(celsius);
  Serial.print((char)176);
  Serial.println("C");
  
  delay(1000);
}

void adc0_init()
{
  // Initialize PC0 (analog input 0 on Arduino board) as input 
  bitClear(DDRC, 0);
  
  // Enable ADC, free running mode, prescaler 128
  ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  // Voltage reference = AVCC, ADC0
  ADMUX |= (1 << REFS0);
  // ADC start conversion
  ADCSRA |= (1 << ADSC);
}
