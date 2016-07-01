/*******************************************************************************
 * Make delay 10 ms with timer 0, normal mode, prescaler 1024, pooling
 * TCNT0 = 256-(0.01s*16000000Hz)/1024 = 156 = 0x64
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
  TCNT0 = 0x64;
  // Normal mode, prescaler 1024
  TCCR0A = 0;
  TCCR0B = (1 << CS02) | (1 << CS00);
  // Wait until timer 0 overflow
  while (!(TIFR0 & (1 << TOV0)));
  // Stop timer 0
  TCCR0B = 0;
  // Clear time 0 overflow flag
  TIFR0 = (1 << TOV0);
}
