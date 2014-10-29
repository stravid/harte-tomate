#include "LEDRenderer.h"

void LEDRenderer::reset() {
  displayCycle = 0;
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
    int patternValue = workPattern[pomodoroTimer.fifth()][i][displayCycle];

    if (patternValue == 1) {
      if (pomodoroTimer.state == WORK) {
        patternValue = 1;
      } else {
        patternValue = 2;
      }
    }

    result[i] = patternValue;
  }

  displayPattern(result);
  displayCycle++;

  if (displayCycle == 4) {
    displayCycle = 0;
  }
}
