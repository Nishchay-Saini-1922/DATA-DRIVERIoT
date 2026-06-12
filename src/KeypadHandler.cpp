#include "KeypadHandler.h"

KeypadHandler::KeypadHandler(uint8_t numRows, uint8_t numCols,
                             const uint8_t* rPins, const uint8_t* cPins)
  : rows(numRows), cols(numCols), rowPins(rPins), colPins(cPins),
    lastKey(0), lastKeyTime(0) {
}

KeypadHandler::~KeypadHandler() {
}

void KeypadHandler::init() {
  Serial.println("  [KeypadHandler] Initializing 4x4 keypad");
  
  for (uint8_t i = 0; i < rows; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }
  
  for (uint8_t i = 0; i < cols; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
  
  Serial.println("  [KeypadHandler] Keypad initialized");
}

char KeypadHandler::getKey() {
  if (millis() - lastKeyTime < DEBOUNCE_DELAY) {
    return 0;
  }
  
  for (uint8_t row = 0; row < rows; row++) {
    digitalWrite(rowPins[row], LOW);
    
    for (uint8_t col = 0; col < cols; col++) {
      if (digitalRead(colPins[col]) == LOW) {
        char key = KEYPAD_KEYS[row][col];
        
        digitalWrite(rowPins[row], HIGH);
        lastKeyTime = millis();
        lastKey = key;
        
        return key;
      }
    }
    
    digitalWrite(rowPins[row], HIGH);
  }
  
  return 0;
}

bool KeypadHandler::keyPressed() {
  return getKey() != 0;
}