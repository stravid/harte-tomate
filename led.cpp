#include "led.h"
 
LED::LED(int pinA, int pinB) {
    pinForRed = pinA;
    pinForGreen = pinB;
    
    pinMode(pinForRed, OUTPUT);
    pinMode(pinForGreen, OUTPUT);
}

LED::~LED() {}

void LED::off() {
  digitalWrite(pinForRed, LOW);
  digitalWrite(pinForGreen, LOW);
}

void LED::green() {
  off();
  digitalWrite(pinForGreen, HIGH);
}

void LED::red() {
  off();
  digitalWrite(pinForRed, HIGH);
}
