#include <Bridge.h>
//#include <HttpClient.h>
#include "SimpleTimer.h"
#include "PomodoroTimer.h"
#include "Button.h"
#include "PomodoroTimerEvents.h"
#include "PomodoroTimerStates.h"
#include "LEDRenderer.h"

PomodoroTimer pomodoroTimer;
SimpleTimer timer;
Button button(2);
LEDRenderer renderer;

void tick() {
  updatePomodoroTimer();
  updateDisplay();
}

void updatePomodoroTimer() {
  int event = pomodoroTimer.update();
  
  if (event == REST_PERIOD_STARTED) {
    Serial.println("Rest period started. (Play sound)");
    renderer.reset();
  }
  
  if (event == REST_PERIOD_ENDED) {
    Serial.println("Rest period ended. (Play sound and make API request)");
    renderer.reset();
  }
}

void updateDisplay() {
  if (pomodoroTimer.state == IDLE) {
    return;
  }
  
  renderer.update(pomodoroTimer);
}

void setup() {                
  Bridge.begin();
  Serial.begin(9600);
  while(!Serial);
  
  timer.setInterval(250, tick);
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
