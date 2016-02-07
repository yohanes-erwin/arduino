/*******************************************************************************
 * Make delay 10ms with timer 0, CTC mode, prescaler 1024, pooling
 * OCR0A = (0.01s*16000000Hz)/1024 = 156 = 0x9C
 *******************************************************************************
 */

void setup()
{
  // PB5 (Arduino digital pin 13) as output 
  bitSet(DDRB, 5);
}

void loop()
{
  // Toggle LED on pin 13
  bitSet(PINB, 5);
  // Delay 1s(100*10ms)
  for (int i = 0; i < 100; i++) 
    T0Delay();
}

// Delay 10ms
void T0Delay()
{
  // Load initial count value
  TCNT0 = 0;
  // Load compare match value
  OCR0A = 0x9C;
  // CTC mode, prescaler 1024
  TCCR0A = (1 << WGM01);
  TCCR0B = (1 << CS02) | (1 << CS00);
  // Wait until timer 0 compare match
  while (!(TIFR0 & (1 << OCF0A)));
  // Stop timer 0
  TCCR0B = 0;
  // Clear OCF0A flag
  TIFR0 = (1 << OCF0A);
}
