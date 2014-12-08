#include "PomodoroTimer.h"

PomodoroTimer::PomodoroTimer() {
  reset();
}

PomodoroTimerEvent PomodoroTimer::update() {
  if (state == IDLE) {
    return NONE;
  }

  unsigned long now = millis();
  durationInMilliseconds += now - millisecondsOfLastUpdate;
  millisecondsOfLastUpdate = now;

  if (state == WORK && durationInMilliseconds >= 25000) {
    setupState(REST);

    return WORK_PERIOD_ENDED;
  }

  if (state == REST && durationInMilliseconds >= 15000) {
    reset();

    return REST_PERIOD_ENDED;
  }

  return NONE;
}

PomodoroTimerEvent PomodoroTimer::buttonPressed() {
	if (state == IDLE) {
    setupState(WORK);

    return WORK_PERIOD_STARTED;
	} else if (state == WORK) {
    reset();

    return WORK_PERIOD_ABORTED;
  } else {
    reset();

    return REST_PERIOD_ABORTED;
  }

  return NONE;
}

int PomodoroTimer::fifth() {
  if (state == WORK) {
    return (int)(durationInMilliseconds / 5000);
  } else if (state == REST) {
    return (int)(durationInMilliseconds / 3000);
  }
}

void PomodoroTimer::resetState() {
  state = IDLE;
}

void PomodoroTimer::resetTime() {
  millisecondsOfLastUpdate = 0;
  durationInMilliseconds = 0;
}

void PomodoroTimer::reset() {
  resetTime();
  resetState();
}

void PomodoroTimer::setupState(PomodoroTimerState s) {
  state = s;
  millisecondsOfLastUpdate = millis();
  durationInMilliseconds = 0;
}
