/*
Pin Connections
===================================      
RFID Module       Tiva C TM4C1294XL LaunchPads        
--------------    -----------------
Pin 1  (SDA)      Pin 52 PQ_1  (CS)
Pin 2  (SCK)      Pin 64 PB_5 (SCK)
Pin 3  (MOSI)     Pin 54 PQ_3(MOSI)
Pin 4  (MISO)     Pin 55 PQ_2(MISO)
Pin 5  (IRQ)      Not connected
Pin 6  (GND)      Pin 60 GND
Pin 7  (RST)      Pin 56 RESET(NRSTDP)
Pin 8  (3V3)      3V3
*/

#include "Mfrc522.h"
#include <SPI.h>

int CS = 52;                                 // chip select pin
int NRSTDP = 56;
Mfrc522 Mfrc522(CS,NRSTDP);
unsigned char serNum[5];

void setup()
{             
  Serial.begin(9600);                        
  Serial.println("Starting RFID-RC522 MIFARE module demonstration...\n");

  SPI.begin();
  digitalWrite(CS, LOW);                    // Initialize the card reader
  pinMode(RED_LED, OUTPUT);                 // Blink LED if card detected
  Mfrc522.Init();  
}

void loop()
{
  unsigned char status;
  unsigned char str[MAX_LEN];
  /*Searching Card, read card type	
  Request(unsigned char reqMode, unsigned char *TagType);
  reqMode: Search method TagType: return card type
  return MI_OK if successed*/
  status = Mfrc522.Request(PICC_REQIDL, str);
  if (status == MI_OK)
  {
    Serial.print("Card detected: ");
    Serial.print(str[0],BIN);
    Serial.print(" , ");
    Serial.print(str[1],BIN);
    Serial.println("");
  }
  /*Read card serial number
  serNum: 4 bytes card serial number, 5th is recheck byte
  return MI_OK if successed*/
  status = Mfrc522.Anticoll(str);
  memcpy(serNum, str, 5);
  if (status == MI_OK)
  {
    digitalWrite(RED_LED, HIGH);              // Card or tag detected!
    Serial.print("The card's number is: ");
    Serial.print(serNum[0]);
    Serial.print(" , ");
    Serial.print(serNum[1]);
    Serial.print(" , ");
    Serial.print(serNum[2]);
    Serial.print(" , ");
    Serial.print(serNum[3]);
    Serial.print(" , ");
    Serial.print(serNum[4]);
    Serial.println("");
 
    delay(1000);
    digitalWrite(RED_LED, LOW); //blink when card deteced
  }
  /*command the card into sleepmode*/
  Mfrc522.Halt();	                        
}


