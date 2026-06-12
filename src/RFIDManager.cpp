#include "RFIDManager.h"
#include "config.h"

RFIDManager::RFIDManager(uint8_t ss, uint8_t rst, uint8_t sck, uint8_t mosi, uint8_t miso)
  : ssPin(ss), rstPin(rst), lastReadTime(0) {
  mfrc522 = nullptr;
  
  SPI.begin(sck, miso, mosi, ss);
}

RFIDManager::~RFIDManager() {
  if (mfrc522 != nullptr) {
    delete mfrc522;
  }
}

void RFIDManager::init() {
  Serial.println("  [RFIDManager] Initializing MFRC522");
  
  mfrc522 = new MFRC522(ssPin, rstPin);
  mfrc522->PCD_Init();
  
  Serial.println("  [RFIDManager] RFID reader initialized");
}

bool RFIDManager::cardAvailable() {
  if (mfrc522 == nullptr) return false;
  
  if (!mfrc522->PICC_IsNewCardPresent()) {
    return false;
  }
  
  if (!mfrc522->PICC_ReadCardSerial()) {
    return false;
  }
  
  return true;
}

String RFIDManager::readCardUID() {
  if (!cardAvailable()) {
    return "";
  }
  
  if (millis() - lastReadTime < READ_DEBOUNCE) {
    mfrc522->PICC_HaltA();
    mfrc522->PCD_StopCrypto1();
    return "";
  }
  
  String uid = "";
  for (byte i = 0; i < mfrc522->uid.size; i++) {
    if (mfrc522->uid.uidByte[i] < 0x10) {
      uid += "0";
    }
    uid += String(mfrc522->uid.uidByte[i], HEX);
  }
  uid.toUpperCase();
  
  mfrc522->PICC_HaltA();
  mfrc522->PCD_StopCrypto1();
  
  lastReadTime = millis();
  
  Serial.println("  [RFIDManager] Card read: " + uid);
  
  return uid;
}

void RFIDManager::storeCard(const String& uid, float value, const String& label) {
  RFIDCard card;
  card.uid = uid;
  card.value = value;
  card.label = label;
  card.lastRead = millis();
  
  cardStorage[uid] = card;
  
  Serial.println("  [RFIDManager] Card stored: " + uid + " = " + String(value));
}

bool RFIDManager::cardExists(const String& uid) {
  return cardStorage.find(uid) != cardStorage.end();
}

RFIDCard RFIDManager::getCard(const String& uid) {
  if (cardExists(uid)) {
    return cardStorage[uid];
  }
  
  RFIDCard empty;
  empty.uid = "";
  empty.value = 0;
  return empty;
}

void RFIDManager::updateCardValue(const String& uid, float value) {
  if (cardExists(uid)) {
    cardStorage[uid].value = value;
    Serial.println("  [RFIDManager] Card updated: " + uid + " = " + String(value));
  }
}

void RFIDManager::removeCard(const String& uid) {
  auto it = cardStorage.find(uid);
  if (it != cardStorage.end()) {
    cardStorage.erase(it);
    Serial.println("  [RFIDManager] Card removed: " + uid);
  }
}

void RFIDManager::clearStorage() {
  cardStorage.clear();
  Serial.println("  [RFIDManager] Card storage cleared");
}