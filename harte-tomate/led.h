#ifndef LED_H
#define LED_H
 
//#include <WProgram.h>
#include <Arduino.h>
 
class LED {
  int pinForGreen;
  int pinForRed;
public:
  LED(int pinA, int pinB);
  ~LED();
  void off();
  void red();
  void green();
};
 
#endif
