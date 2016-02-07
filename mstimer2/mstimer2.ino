#include <MsTimer2.h>

void setup()
{
  pinMode(13, OUTPUT);
  
  // Toggle LED on pin 13 each second
  MsTimer2::set(1000, flash);
  MsTimer2::start();
}

void loop() 
{ 
}

void flash()
{
  static boolean output = HIGH;
  digitalWrite(13, output);
  output = !output;
}
