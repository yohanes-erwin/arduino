// Pin definitions
#define TRIMPOT    0
#define PHOTORES   1
#define LED        9

// Tuning parameters
float Kp = 10;
float Ki = 1;
float Kd = 0.5;

// Variable for store value from ADC
double trimpotValue;
double lightValue;
// Variable for PID control
double setPoint, processVariable, pidOutput;
double pidOutputMin = 0, pidOutputMax = 255;
double error, lastError = 0;
const int pidSampleRate = 10;
unsigned long nowPidCompute = 0;
unsigned long lastPidCompute = 0;
// Variable for serial data send
const long serialDataSendInterval = 500;
unsigned long nowSerialDataSend = 0;
unsigned long lastSerialDataSend = 0;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  /* Get input */
  // Read trimpot value
  trimpotValue = analogRead(TRIMPOT);
  // Read light value
  lightValue = analogRead(PHOTORES);
  // Scale trimpot value for PID set point input
  setPoint = map(trimpotValue, 0, 1023, 0, 255);
  // Scale light value for PID process variable input
  processVariable = map(lightValue, 0, 1023, 0, 255);
  
  /* PID calculation */
  // Keep track of the elapsed time
  nowPidCompute = millis();
  if (nowPidCompute-lastPidCompute >= pidSampleRate)
  {
    // Calculate error
    double error = setPoint - processVariable;
    
    // Caluculate PID output  
    pidOutput = (Kp * error) + (Ki * (error + lastError)) + (Kd * (error - lastError));  

    // Linit PID output
    if (pidOutput > pidOutputMax)
      pidOutput = pidOutputMax;
    if (pidOutput < pidOutputMin)
      pidOutput = pidOutputMin;
    
    // Save previous error for derivative
    lastError = error;
    
    // Reference the next PID calculation to this point
    lastPidCompute = nowPidCompute;
  }
  
  /* Set output */
  // Power the LED with output value from PID controller
  analogWrite(LED, pidOutput);
  
  /* Serial data send */
  // Keep track of the elapsed time
  nowSerialDataSend = millis();
  // If enough time has passed since last data send
  if (nowSerialDataSend-lastSerialDataSend > serialDataSendInterval)
  {
    // Send PID control data log
    Serial.println(processVariable);
    
    // Reference the next data send to this point
    lastSerialDataSend = nowSerialDataSend;
  }
}
