#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5  // ESP32 pin GIOP5 
#define RST_PIN 22 // ESP32 pin GIOP27 

void setupRFID();
int touchedRFID();
void getRFID();