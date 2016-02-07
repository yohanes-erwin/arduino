extern volatile unsigned long timer0_millis;

// Rx complete interrupt service routine
ISR(USART_RX_vect)
{
  // Read UDR0
  char c = UDR0;
  
  if (c == 'H') 
    bitSet(PORTB, 5);
  else if (c == 'L')
    bitClear(PORTB, 5); 
}

void setup()
{
  // PB5 (Arduino digital pin 13) as output 
  bitSet(DDRB, 5);
  // PC0 (Arduino analog input pin 0) as input 
  bitClear(DDRC, 0);
  
  uart_init(9600);
  
  // Enable ADC, free running mode, prescaler 128
  ADCSRA |= (1 << ADEN) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  // Voltage reference = AVCC, ADC0
  ADMUX |= (1 << REFS0);
  // ADC start conversion
  ADCSRA |= (1 << ADSC);
  
  // Reset millis timer
  timer0_millis = 0;
  // Wait for ADC to finish conversion
  while (timer0_millis < 1);
}

void loop()
{
  float millivolts = (ADC/1024.0) * 5 * 1000;
  int c = round(millivolts / 10);
  int f = round((c*9/5) + 32);
  
  // Send data to UART
  uart_puti(c);
  uart_putc(176);
  uart_puts("C,");
  uart_puti(f);
  uart_putc(176);
  uart_puts("F.");
  
  // Reset millis timer
  timer0_millis = 0;
  // Wait 1 second
  while (timer0_millis < 1000);
}

// Function for UART initialization
void uart_init(unsigned long baud_rate)
{
  // Clear U2X0 (double UART transmission speed register) 
  UCSR0A = 0;
  // Enable Rx complete interrupt, receiver, transmitter
  UCSR0B = (1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0);
  // 8 data bits, no parity bits, 1 stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  // Set baud rate
  UBRR0 = (F_CPU/(16*baud_rate)) - 1;
}

// Function to transmit a single character
void uart_putc(char c)
{
  // Wait for transmit buffer to be empty
  while (!(UCSR0A & (1 << UDRE0)));
  // Transmit character out the UART
  UDR0 = c;
}

// Function to transmit a string of characters
void uart_puts(char *s)
{
  // While there is a character
  while (*s)
  {
    // Transmit a character
    uart_putc(*s);
    // Go to the next character
    s++;
  }
}

// Function to transmit an integer
void uart_puti(long i)
{
  // Character buffer to build string in
  char s[25];
  // Convert integer to ASCII string, base 10
  itoa(i, s, 10);
  // Transmit string
  uart_puts(s);
}
