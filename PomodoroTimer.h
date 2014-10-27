#ifndef POMODORO_TIMER_H
#define POMODORO_TIMER_H

#include <Arduino.h>

class PomodoroTimer {
public:
  PomodoroTimer();
  void buttonPressed();
  int update();
  int fifth();
  int state;
  unsigned long durationInMilliseconds;
private:
  unsigned long millisecondsOfLastUpdate;
};

#endif
