/*******************************************************************************
 * Make delay 1s with timer 1, normal mode, prescaler 256, interrupt
 * TCNT1 = 65536-(1s*16000000Hz)/256 = 3036 = 0x0BDC
 *******************************************************************************
 */

// Timer 1 overflow interrupt every 1s
ISR(TIMER1_OVF_vect)
{
  // Toggle LED on pin 13
  bitSet(PINB, 5);
  // Load initial count value for next count
  TCNT1 = 0x0BDC; 
}

void setup()
{
  init_timer1();
  // PB5 (Arduino digital pin 13) as output 
  bitSet(DDRB, 5);
}

void loop()
{
}

// Timer 1 initialization
void init_timer1()
{
  // Load initial count value
  TCNT1 = 0x0BDC;
  // Normal mode, prescaler 256
  TCCR1A = 0;
  TCCR1B = (1 << CS12);
  // Enable timer 1 overflow interrupt
  TIMSK1 = (1 << TOIE1);
  // Enable global interrupt
  sei();
}
