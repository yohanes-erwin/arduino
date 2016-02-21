#include <PID_v1.h>

// Pin definitions
#define TRIMPOT   0
#define PHOTORES  1
#define LED       9

// Tuning parameters
float Kp = 10;
float Ki = 1;
float Kd = 0;

double lightLevel;
double setPoint, input, output;
PID myPID(&input, &output, &setPoint, Kp, Ki, Kd, DIRECT);
const int sampleRate = 1;
const long serialPing = 500;
unsigned long now = 0;
unsigned long lastMessage = 0;

void setup()
{
  // Read lihgt level
  lightLevel = analogRead(PHOTORES);
  // Scale light level for PID input
  input = map(lightLevel, 0, 1023, 0, 255);
  // Read and scale set point from trimpot
  setPoint = map(analogRead(TRIMPOT), 0, 1023, 0, 255);  
  
  Serial.begin(9600);
  // Start PID controller
  myPID.SetMode(AUTOMATIC);
  // Assign the sample rate of PID controller
  myPID.SetSampleTime(sampleRate);
  Serial.print("PID control begin.\n\n");
  // Serial data will be received relative to this point
  lastMessage = millis();
}

void loop()
{
  // Read lihgt level
  lightLevel = analogRead(PHOTORES);
  // Scale light level for PID input
  input = map(lightLevel, 0, 1023, 0, 255);
  // Read and scale set point from trimpot
  setPoint = map(analogRead(TRIMPOT), 0, 1023, 0, 255);  
  
  // Calculate PID output at specified sample time
  myPID.Compute();
  
  // Power the LED with output value from PID controller
  analogWrite(LED, output);
  // Keep track of the elapsed time
  now = millis();
  
  // If enough time has passed since last data send
  if (now-lastMessage > serialPing)
  {
    // Send PID controller data log
    Serial.print("Setpoint = ");
    Serial.print(setPoint);
    Serial.print(" Input = ");  
    Serial.print(input);
    Serial.print(" Output = ");
    Serial.println(output);
    
    // Tuning parameters can be retrieved from the serial monitor:
    // 10,2,0.5 set Kp to 10, Ki to 2, Kd to 0.5
    if (Serial.available() > 0)
    {
      for (int i = 0; i < 4; i++)
      {
        switch (i)
        {
          case 0:
            Kp = Serial.parseFloat();
            break;
          case 1:
            Ki = Serial.parseFloat();
            break;
          case 2:
            Kd = Serial.parseFloat();
            break;
          case 3:
            for (int j = Serial.available(); j == 0; j--)
            {
              Serial.read();
            }
            break;  
        }
      }
      
      // Display new tuning parameters
      Serial.print("\nKp, Ki, Kd = ");
      Serial.print(Kp);
      Serial.print(", ");
      Serial.print(Ki);
      Serial.print(", ");
      Serial.print(Kd);
      Serial.print("\n\n");
      // Set the tuning parameters to the PID controller
      myPID.SetTunings(Kp, Ki, Kd);
    }
    // Reference the next data send to this point
    lastMessage = now; 
  }
}

