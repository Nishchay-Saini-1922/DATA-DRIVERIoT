/*
 * Joystick Handler - Manages analog joystick with push button
 */

#ifndef JOYSTICK_HANDLER_H
#define JOYSTICK_HANDLER_H

#include <Arduino.h>
#include "config.h"

class JoystickHandler {
public:
  struct JoystickState {
    bool up;
    bool down;
    bool left;
    bool right;
    bool pressed;
  };

private:
  uint8_t xPin, yPin, btnPin;
  JoystickState currentState;
  unsigned long lastButtonTime;
  const unsigned long BUTTON_DEBOUNCE = 50;
  
public:
  JoystickHandler(uint8_t x, uint8_t y, uint8_t btn);
  ~JoystickHandler();
  
  void init();
  JoystickState getState();
  void update();
  
  bool isUp();
  bool isDown();
  bool isLeft();
  bool isRight();
  bool isPressed();
};

#endif