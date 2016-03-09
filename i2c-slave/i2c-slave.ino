/**
  ******************************************************************************
  * @author	Yohanes Erwin Setiawan
  * @date	8 March 2016
  * @brief      Turns Arduino to I2C slave device. We can send data byte "0x01" 
  *             from master device to turn on LED blinking on Arduino. 
  *             To turn off LED blinking, we can send "0x00" from master device.
  *             Master can also read LED blinking status (off/on) from Arduino 
  *             which returns 0 or 1.
  ******************************************************************************
  */
#include <Wire.h>

#define OWN_ADDRESS  0x08
#define LED_PIN      13

int ledBlink = 0;

void receiveEvent(int bytes) 
{
  // Read received data
  ledBlink = Wire.read();
}

void requestEvent()
{
  // Send LED blinking status
  Wire.write(ledBlink);
}

void setup() 
{
  pinMode (LED_PIN, OUTPUT);
  
  // Start the I2C bus as slave
  Wire.begin(OWN_ADDRESS); 
  // Attach a function to trigger when something is received
  Wire.onReceive(receiveEvent);
  // Attach a function to trigger when something is requested
  Wire.onRequest(requestEvent);
}

void loop() 
{
  // If received data is 1, then blink LED for 250 ms
  if (ledBlink == 1) 
  {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
  }
  // If received data is 0, then turn off LED
  else if (ledBlink == 0) 
  {
    digitalWrite(LED_PIN, LOW);
  }
}
