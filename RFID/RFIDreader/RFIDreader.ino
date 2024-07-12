#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN     9           // Configurable, typically a pin connected to RST
#define SS_PIN      10          // Configurable, typically a pin connected to SDA

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);   // Initialize serial communications

  SPI.begin();          // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522

  Serial.println("RFID Ready");
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial() ) {
    delay(50);
    return;
  }

  // Show some details of the PICC (Card)
  Serial.print("RFID Tag UID:");
  String tag = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     tag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tag.toUpperCase();
  Serial.println(tag);
  
  mfrc522.PICC_HaltA();  // Halt PICC
  mfrc522.PCD_StopCrypto1(); // Stop encryption on PCD
}
