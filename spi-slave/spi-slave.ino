/**
  ******************************************************************************
  * @author	Yohanes Erwin Setiawan
  * @date	10 March 2016
  * @brief      Turns Arduino to SPI slave device. We can send data char '1' 
  *             from master device to turn on LED blinking on Arduino. 
  *             To turn off LED blinking, we can send '0' from master device.
  *             Master can also read LED blinking status (off/on) from Arduino 
  *             by sending '?' first, then read the LED blinking status 
  *             which returns 0 or 1.
  ******************************************************************************
  */
 
#define LED_PIN  9

volatile uint8_t led_blink = 0;

ISR(SPI_STC_vect)
{
  uint8_t data_byte = SPDR;

  switch (data_byte)
  {
    case '0':
      led_blink = 0;
      SPDR = 0;  
    break;
    case '1':
      led_blink = 1;
      SPDR = 0;  
    break;
    case '?':
      // Place LED blinking status in SPDR register for next transfer
      SPDR = led_blink;  
    break;
  }  
}

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  
  // Set MISO pin as output
  pinMode(MISO, OUTPUT);
  // Turn on SPI in slave mode
  SPCR |= (1 << SPE);
  // Turn on interrupt
  SPCR |= (1 << SPIE);
}

void loop() 
{
  // If LED blink status is on, then blink LED for 250ms
  if (led_blink == 1)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);  
  }
  else if (led_blink == 0)
  {
    digitalWrite(LED_PIN, LOW); 
  }
}
