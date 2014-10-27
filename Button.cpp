#include "Button.h"

Button::Button(int p) {
  pin = p;
  pinMode(pin, INPUT);
  previousIsPressed = false;
}

bool Button::pressed() {
  bool isPressed = !(digitalRead(pin) == LOW);
  bool countsAsButtonPress = false;

  if (!previousIsPressed && isPressed) {
    firstPressedAt = millis();
  }

  if (!isPressed && previousIsPressed && isLongEnoughPressed()) {
    countsAsButtonPress = true;
  }

  previousIsPressed = isPressed;

  return countsAsButtonPress;
}

bool Button::isLongEnoughPressed() {
  return true;
  return millis() - firstPressedAt > 100;
}
