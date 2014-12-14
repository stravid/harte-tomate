#ifndef POMODORO_TIMER_H
#define POMODORO_TIMER_H

#include <Arduino.h>
#include "PomodoroTimerEvents.h"
#include "PomodoroTimerStates.h"

class PomodoroTimer {
public:
  PomodoroTimer();
  PomodoroTimerEvent buttonPressed();
  PomodoroTimerEvent update();
  int fifth();
  PomodoroTimerState state;
  void setupRestPeriod();
private:
  unsigned long durationInMilliseconds;
  unsigned long millisecondsOfLastUpdate;
  void reset();
  void resetState();
  void resetTime();
  void setupState(PomodoroTimerState state);
};

#endif
