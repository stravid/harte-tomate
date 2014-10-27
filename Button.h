#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button {
  public:
    Button(int pin);
    bool pressed();

  private:
    bool previousIsPressed;
    bool isLongEnoughPressed();
    unsigned long firstPressedAt;
    int pin;
};
#endif
