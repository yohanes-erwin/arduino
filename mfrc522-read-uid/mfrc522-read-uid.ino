// MFRC522 pin connection
// RST -> 9, SDA(SS) -> 10, MOSI -> 11, MISO -> 12, SCK -> 13

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9           
#define SS_PIN    10  

MFRC522 mfrc522(SS_PIN, RST_PIN);
byte readCard[7];

void setup() 
{
  Serial.begin(9600);
    
  SPI.begin();
  mfrc522.PCD_Init();
  
  Serial.println("Tap Your ID Card...");
}

void loop() 
{
  // Check if there is a new PICC
  if (!mfrc522.PICC_IsNewCardPresent())
    return;
  // Check if a UID can be read 
  if (!mfrc522.PICC_ReadCardSerial())
    return;
        
  // Read and print the UID to serial monitor      
  for (int i = 0; i < mfrc522.uid.size; i++) 
  {
    readCard[i] = mfrc522.uid.uidByte[i];
    
    Serial.print(readCard[i] < 0x10 ? " 0" : " ");
    Serial.print(readCard[i], HEX);
  }
  Serial.print("\n");
  
  // Instruct a PICC in state active to go to state halt
  mfrc522.PICC_HaltA();
}
