// Arduino digital input 2 (PD2 on ATmega328)
#define IR_PIN      PIND
#define IR_PIN_BIT  2

// Maximum pulse length in milliseconds that can be listened
#define MAX_PULSE    65000
// Timing resolution in microseconds
#define RESOLUTION   20

// For storing timing pulse pairs
// A pair of timing pulse is high and low timing pulse
uint16_t pulses[100][2];
uint8_t currentPulseIndex = 0;

void setup() {
  Serial.begin(9600);
  Serial.print("Ready to decode IR.\n");
}

void loop() {
  // Temporary storage for timing pulse
  uint16_t highPulse, lowPulse = 0;
  
  // While pin is still high
  while (IR_PIN & (1 << IR_PIN_BIT))
  {
    // Increment timing pulse
    highPulse++;
    delayMicroseconds(RESOLUTION); 
    
    // If the pulse is too long, then timeout occurs
    // Either nothing was received or the code is finished
    if ((highPulse >= MAX_PULSE) && (currentPulseIndex != 0))
    {
      printPulses();
      currentPulseIndex = 0;
      return;   
    }
  }
  // Timeout not occurs, then store timing pulse
  pulses[currentPulseIndex][0] = highPulse;
  
  // For low pulse
  while (!(IR_PIN & (1 << IR_PIN_BIT)))
  {
    lowPulse++;
    delayMicroseconds(RESOLUTION);
    
    if ((lowPulse >= MAX_PULSE) && (currentPulseIndex != 0))
    {
      printPulses();
      currentPulseIndex = 0;
      return;   
    }
    pulses[currentPulseIndex][1] = lowPulse; 
  }
  
  // Increment timing pulse index for next timing pulse pair
  currentPulseIndex++;
}

// Print pulses length to serial monitor
void printPulses()
{
  Serial.print("\nReceived:\nHIGH pulse, LOW Pulse\n");
  for (uint8_t i = 0; i < currentPulseIndex - 1; i++)
  {
    // Print high pulse in microseconds
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
    Serial.print(" us, ");
    // Print low pulse in microseconds
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.print(" us\n");  
  }
}
