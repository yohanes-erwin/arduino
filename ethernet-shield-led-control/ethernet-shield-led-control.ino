#include <SPI.h>
#include <Ethernet.h>

// Arduino server MAC address
uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// Arduino server IP address
IPAddress ip(192, 168, 137, 3);
// Arduino server port
const int port = 23;

// Ethernet server
EthernetServer server(port);

// For store command from client
String cmd;

void setup() 
{
  // Set digital pin 2 (PD2) as output for LED
  bitSet(DDRD, 2);
  
  Serial.begin(9600);
	
  // Ethernet server initialization
  Ethernet.begin(mac, ip);
  server.begin();
	
  // Print Arduino server IP address to serial monitor
  Serial.print("Server IP Address: ");
  Serial.println(Ethernet.localIP());
}

void loop() 
{
  EthernetClient client = server.available();
  
  if (client.available()) 
  {
    // Read char until new line
    char c = client.read();	
    if (c != '\n') 
    {
      // Add received char to string variable 
      cmd += c;
    } 
    else 
    {
      // Print received command to serial monitor
      Serial.println("Command: " + cmd);
			
      // Process the received command
      processCommand(cmd);
			
      // Clear variable for receive next command
      cmd = "";
    }
  }
}

void processCommand(String cmd) 
{
  if (cmd == "led=1") 
  {
    // Turn on LED
    bitSet(PORTD, 2);
  } 
  else if (cmd == "led=0") 
  {
    // Turn off LED
    bitClear(PORTD, 2);
  } 
  else if (cmd == "led=?") 
  {
    // Read LED status then send it to client
    if (bitRead(PORTD, 2)) 
    {
      server.println("led=1");
    } 
    else 
    {
      server.println("led=0");
    }
  }
}
