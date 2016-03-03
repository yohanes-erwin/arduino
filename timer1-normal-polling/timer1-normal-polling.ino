/*******************************************************************************
 * Make delay 1s with timer 1, normal mode, prescaler 256, pooling
 * TCNT1 = 65536-(1s*16000000Hz)/256 = 3036 = 0x0BDC
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
  TCNT1 = 0x0BDC;
  // Normal mode, prescaler 256
  TCCR1A = 0;
  TCCR1B = (1 << CS12);
  // Wait until timer 1 overflow
  while (!(TIFR1 & (1 << TOV1)));
  // Stop timer 1
  TCCR1B = 0;
  // Clear timer 1 overflow flag
  TIFR1 = (1 << TOV1);
}

