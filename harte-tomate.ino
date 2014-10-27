#include "led.h"
#include <Bridge.h>
//#include <HttpClient.h>
#include "SimpleTimer.h"
#include "PomodoroTimer.h"
#include "Button.h"
#include "PomodoroTimerEvents.h"
#include "PomodoroTimerStates.h"

LED leds[5] = { LED(12, 11), LED(10, 9), LED(8, 7), LED(6, 5), LED(4, 3) };

PomodoroTimer pomodoroTimer;
SimpleTimer timer;
Button button(2);

int pattern[5][5][4] = {
  {
    { 1, 0, 1, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
  },
  {
    { 1, 1, 1, 1 },
    { 1, 0, 1, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
  },
  {
    { 1, 1, 1, 1 },
    { 1, 1, 1, 1 },
    { 1, 0, 1, 0 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
  },
  {
    { 1, 1, 1, 1 },
    { 1, 1, 1, 1 },
    { 1, 1, 1, 1 },
    { 1, 0, 1, 0 },
    { 0, 0, 0, 0 }
  },
  {
    { 1, 1, 1, 1 },
    { 1, 1, 1, 1 },
    { 1, 1, 1, 1 },
    { 1, 1, 1, 1 },
    { 1, 0, 1, 0 }
  }
};

int displayCycle = 0;

void tick() {
  int event = pomodoroTimer.update();
  
  if (event == REST_PERIOD_STARTED) {
    Serial.println("Rest period started. (Play sound)");
    displayCycle = 0;
  }
  
  if (event == REST_PERIOD_ENDED) {
    Serial.println("Rest period ended. (Play sound and make API request)");
    displayCycle = 0;
  }
}

void updateDisplay() {
  if (pomodoroTimer.state == IDLE) {
    return;
  }
  
  int result[5];

  for (int i = 0; i < 5; i++) {
    int patternValue = pattern[pomodoroTimer.fifth()][i][displayCycle];

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

void setup() {                
  Bridge.begin();
  Serial.begin(9600);
  while(!Serial);
  
  timer.setInterval(1000, tick);
  timer.setInterval(250, updateDisplay);
}

void loop() {
  timer.run();

  if (button.pressed()) {
    PomodoroTimerEvent event = pomodoroTimer.buttonPressed();

    if (event == WORK_PERIOD_STARTED) {
      Serial.println("Work started. (Make API request)");
    }

    if (event == PERIOD_ABORTED) {
      Serial.println("Period aborted. (Make API request)");
    }
  }
}

void displayPattern(int pattern[]) {  
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
