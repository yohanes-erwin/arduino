/*******************************************************************************
 * Make delay 10ms with timer 0, CTC mode, prescaler 1024, interrupt
 * OCR0A = (0.01s*16000000Hz)/1024 = 156 = 0x9C
 *******************************************************************************
 */

int i = 0;

// Timer 0 compare match a interrupt every 10ms
ISR(TIMER0_COMPA_vect)
{
  // Increment i to make delay 1s(100*10ms)
  i++;
  if (i == 100)
  {
    // Toggle LED on pin 13
    bitSet(PINB, 5);
    // Reset
    i = 0;
  }
  // Load compare match value for next count
  OCR0A = 0x9C;
}

void setup()
{
  init_timer0();
  // PB5 (Arduino digital pin 13) as output 
  bitSet(DDRB, 5);
}

void loop()
{
}

// Timer 0 initialization
void init_timer0()
{
  // Load initial count value
  TCNT0 = 0;
  // Load compare match value
  OCR0A = 0x9C;
  // CTC mode, prescaler 1024
  TCCR0A = (1 << WGM01);
  TCCR0B = (1 << CS02) | (1 << CS00);
  // Enable timer 0 compare match a interrupt
  TIMSK0 = (1 << OCIE0A);
  // Enable global interrupt
  sei();
}

