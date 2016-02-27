extern volatile unsigned long timer0_millis;

void setup() 
{
  // USART initialization
  usart_init(9600);
}

void loop() 
{
  // Send "$1000Hello, World!"
  usart_putc('$');
  usart_puti(1000);
  usart_puts("Hello, World!\n");
  
  // Reset millis timer
  timer0_millis = 0;
  // Wait 1s
  while (timer0_millis < 1000);
}

void usart_init(unsigned long baud_rate)
{
  // Clear U2X0 (double USART transmission spedd register)
  UCSR0A = 0;
  // Enable USART transmitter
  UCSR0B = (1 << TXEN0);
  // 8 data bits, no parity bits, 1 stop bit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  // Set baud rate
  UBRR0 = (F_CPU/(16*baud_rate)) - 1;  
}

// Function to transmit a single character
void usart_putc(char c)
{
  // Wait for transmit buffer to be empty
  while (!(UCSR0A & (1 << UDRE0)));
  // Transmit character out the USART
  UDR0 = c;  
}

// Function to transmit a string
void usart_puts(char* s)
{
  // While there is a character
  while (*s)
  {
    // Transmit a character
    usart_putc(*s);
    // Go to the next character
    s++; 
  }
}

// Function to transmit an integer
void usart_puti(long i)
{
  // Character buffer to build string in
  char s[25];
  // Convert integer to ASCII string, base 10
  itoa(i, s, 10);
  // Transmit string
  usart_puts(s);  
}
