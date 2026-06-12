/*
 * Keypad Handler - Manages 4x4 matrix keypad
 */

#ifndef KEYPAD_HANDLER_H
#define KEYPAD_HANDLER_H

#include <Arduino.h>
#include "config.h"

class KeypadHandler {
private:
  uint8_t rows, cols;
  const uint8_t* rowPins;
  const uint8_t* colPins;
  char lastKey;
  unsigned long lastKeyTime;
  const unsigned long DEBOUNCE_DELAY = 50;
  
public:
  KeypadHandler(uint8_t numRows, uint8_t numCols, 
                const uint8_t* rPins, const uint8_t* cPins);
  ~KeypadHandler();
  
  // Initialization
  void init();
  
  // Key reading
  char getKey();
  bool keyPressed();
  
  // Key classification
  static bool isNumber(char key) { return key >= '0' && key <= '9'; }
  static bool isLetter(char key) { return (key >= 'A' && key <= 'D'); }
  static bool isSpecial(char key) { return (key == '*' || key == '#'); }
};

#endif