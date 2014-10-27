#include "PomodoroTimer.h"

PomodoroTimer::PomodoroTimer() {
  millisecondsOfLastUpdate = 0;
  durationInMilliseconds = 0;
  state = 0;
}

// 0 = not running
// 1 = rest period started
// 2 = rest period finished
int PomodoroTimer::update() {
  if (state == 0) {
    return 0;
  }

  unsigned long now = millis();
  
//    Serial.println(state);
//    Serial.println(now);
//    Serial.println(millisecondsOfLastUpdate);
//    Serial.println(durationInMilliseconds);

  if (millisecondsOfLastUpdate > 0) {
    durationInMilliseconds += now - millisecondsOfLastUpdate;
  }
  
  millisecondsOfLastUpdate = now;
  
  Serial.println(durationInMilliseconds / 1000);

  if (state == 1 && durationInMilliseconds >= 25000) {
    state = 2;
    millisecondsOfLastUpdate = 0;
    durationInMilliseconds = 0;
    Serial.println("Work period finished");
    Serial.println("Rest period started");
    return 1;
  }

  if (state == 2 && durationInMilliseconds >= 15000) {
//    Serial.println(now);
//    Serial.println(state);
//    Serial.println(millisecondsOfLastUpdate);
//    Serial.println(durationInMilliseconds);
    state = 0;
    millisecondsOfLastUpdate = 0;
    durationInMilliseconds = 0;
    Serial.println("Rest period finished");
    return 2;
  }
  
  return 0;
}

void PomodoroTimer::buttonPressed() {
	if (state == 0) {
		state = 1;
    millisecondsOfLastUpdate = millis();
    durationInMilliseconds = 0;
		Serial.println("Work period started");
	} else {
    state = 0;
    millisecondsOfLastUpdate = 0;
    durationInMilliseconds = 0;
    Serial.println("Period aborted");
  }
}

int PomodoroTimer::fifth() {
  if (state == 1) {
    return (int)(durationInMilliseconds / 5000);
  } else if (state == 2) {
    return (int)(durationInMilliseconds / 3000);
  }
}
