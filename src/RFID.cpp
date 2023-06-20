#include "RFID.h"

MFRC522 rfid(SS_PIN, RST_PIN);

void setupRFID() {
  SPI.begin(); // init SPI bus
  rfid.PCD_Init(); // init MFRC522

  Serial.println("Tap an RFID/NFC tag on the RFID-RC522 reader");
}

int touchedRFID() {
  return rfid.PICC_IsNewCardPresent();
}

String getRFID() {
  String id = "";
  if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
    Serial.print("RFID/NFC Tag Type: ");
    Serial.println(rfid.PICC_GetTypeName(piccType));
    // print UID in Serial Monitor in the hex format
    Serial.print("UID:");
    for (int i = 0; i < rfid.uid.size; i++) {
      Serial.print(rfid.uid.uidByte[i], HEX);
      id.concat(String(rfid.uid.uidByte[i],HEX));
    }
    Serial.println();
    rfid.PICC_HaltA(); // halt PICC
    rfid.PCD_StopCrypto1(); // stop encryption on PCD
  }
  return id;
}
