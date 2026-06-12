/*
 * RFID Manager - Manages MFRC522 RFID reader
 */

#ifndef RFID_MANAGER_H
#define RFID_MANAGER_H

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <map>

struct RFIDCard {
  String uid;
  float value;
  String label;
  unsigned long lastRead;
};

class RFIDManager {
private:
  MFRC522* mfrc522;
  uint8_t ssPin, rstPin;
  std::map<String, RFIDCard> cardStorage;
  unsigned long lastReadTime;
  const unsigned long READ_DEBOUNCE = 500;
  
public:
  RFIDManager(uint8_t ss, uint8_t rst, uint8_t sck, uint8_t mosi, uint8_t miso);
  ~RFIDManager();
  
  void init();
  
  bool cardAvailable();
  String readCardUID();
  
  void storeCard(const String& uid, float value, const String& label = "");
  bool cardExists(const String& uid);
  RFIDCard getCard(const String& uid);
  void updateCardValue(const String& uid, float value);
  void removeCard(const String& uid);
  
  int getStoredCardCount() { return cardStorage.size(); }
  void clearStorage();
  
  MFRC522* getMFRC522() { return mfrc522; }
};

#endif