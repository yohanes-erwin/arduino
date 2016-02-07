extern volatile unsigned long timer0_millis;

void setup()
{
  // UART initialization 
  uart_init(9600);
}

void loop()
{
  // Send "$1000Hello, World"
  uart_putc('$');
  uart_puti(1000);
  uart_puts("Hello, World!\n");
  
  // Reset millis timer
  timer0_millis = 0;
  // Wait 1s
  while (timer0_millis < 1000);
}

void uart_init(unsigned long baud_rate)
{
  // Clear U2X0 (double UART transmission speed register) 
  UCSR0A = 0;
  // Enable UART transmitter
  UCSR0B = (1 << TXEN0);
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
