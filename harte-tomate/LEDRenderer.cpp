#include "LEDRenderer.h"

void LEDRenderer::reset() {
  displayCycle = 0;
  int pattern[5] = { 0, 0, 0, 0, 0 };
  displayPattern(pattern);
}

void LEDRenderer::allGreen() {
  int pattern[5] = { 1, 1, 1, 1, 1 };
  displayPattern(pattern);
}

void LEDRenderer::allRed() {
  int pattern[5] = { 2, 2, 2, 2, 2 };
  displayPattern(pattern);
}

void LEDRenderer::displayPattern(int pattern[]) {
  for (int i = 0; i < 5; i++) {
    if (pattern[i] == 0) {
      leds[i].off();
    }

    if (pattern[i] == 1) {
      leds[i].green();
    }

    if (pattern[i] == 2) {
      leds[i].red();
    }
  }
}

void LEDRenderer::update(PomodoroTimer pomodoroTimer) {
  int result[5];

  for (int i = 0; i < 5; i++) {
    if (pomodoroTimer.state == WORK) {
      result[i] = workPattern[pomodoroTimer.fifth()][i][displayCycle];
    } else {
      result[i] = restPattern[pomodoroTimer.fifth()][i][displayCycle];
    }
  }

  displayPattern(result);
  displayCycle++;

  if (displayCycle == 4) {
    displayCycle = 0;
  }
}
