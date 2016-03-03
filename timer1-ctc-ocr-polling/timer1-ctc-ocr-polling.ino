/*******************************************************************************
 * Make delay 1s with timer 1, CTC mode(top = OCR1A), prescaler 256, pooling
 * OCR1A = (1s*16000000Hz)/256 = 62500 = 0xF424
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
  // Delay 1s
  T1Delay();
}

// Delay 1s
void T1Delay()
{
  // Load initial count value
  TCNT1 = 0;
  // Load compare match value
  OCR1A = 0xF424;
  // CTC mode, prescaler 256
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS12);
  // Wait until timer 1 compare match
  while (!(TIFR1 & (1 << OCF1A)));
  // Stop timer 1
  TCCR1B = 0;
  // Clear OCF1A flag
  TIFR1 = (1 << OCF1A);
}
