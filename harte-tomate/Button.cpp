#include "Button.h"

Button::Button(int p) {
  pin = p;
  pinMode(pin, INPUT);
  previousIsPressed = false;
  lockedAt = 0;
}

bool Button::pressed() {
  if (isLocked()) {
    return false;
  }

  bool isPressed = (digitalRead(pin) == HIGH);
  bool countsAsButtonPress = false;

  if (isPressed && !previousIsPressed) {
    firstPressedAt = millis();
  }

  if (!isPressed && previousIsPressed) {
    if (isLongEnoughPressed()) {
      countsAsButtonPress = true;
      lockedAt = millis();
    }
  }

  previousIsPressed = isPressed;

  return countsAsButtonPress;
}

bool Button::isLongEnoughPressed() {
  return millis() - firstPressedAt > 50;
}

bool Button::isLocked() {
  return millis() - lockedAt < 1000;
}
