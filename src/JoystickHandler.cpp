#include "JoystickHandler.h"

JoystickHandler::JoystickHandler(uint8_t x, uint8_t y, uint8_t btn)
  : xPin(x), yPin(y), btnPin(btn), lastButtonTime(0) {
  currentState = {false, false, false, false, false};
}

JoystickHandler::~JoystickHandler() {
}

void JoystickHandler::init() {
  Serial.println("  [JoystickHandler] Initializing joystick");
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(btnPin, INPUT_PULLUP);
  
  Serial.println("  [JoystickHandler] Joystick initialized");
}

JoystickHandler::JoystickState JoystickHandler::getState() {
  update();
  return currentState;
}

void JoystickHandler::update() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);
  
  currentState.up = (yValue > 3000);
  currentState.down = (yValue < 1000);
  currentState.left = (xValue < 1000);
  currentState.right = (xValue > 3000);
  
  if (millis() - lastButtonTime > BUTTON_DEBOUNCE) {
    currentState.pressed = (digitalRead(btnPin) == LOW);
    if (currentState.pressed) {
      lastButtonTime = millis();
    }
  } else {
    currentState.pressed = false;
  }
}

bool JoystickHandler::isUp() {
  update();
  return currentState.up;
}

bool JoystickHandler::isDown() {
  update();
  return currentState.down;
}

bool JoystickHandler::isLeft() {
  update();
  return currentState.left;
}

bool JoystickHandler::isRight() {
  update();
  return currentState.right;
}

bool JoystickHandler::isPressed() {
  update();
  return currentState.pressed;
}