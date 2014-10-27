#include "led.h"
#include <Bridge.h>
//#include <HttpClient.h>
#include "SimpleTimer.h"
#include "PomodoroTimer.h"
#include "Button.h"

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
  
  if (event == 1) {
    Serial.println("Play sound, and start resting");
    displayCycle = 0;
  }
  
  if (event == 2) {
    Serial.println("Play sound, and make web request");
    displayCycle = 0;
  }
}

void updateDisplay() {
  if (pomodoroTimer.state == 0) {
    return;
  }
  
  int result[5];

  for (int i = 0; i < 5; i++) {
    int patternValue = pattern[pomodoroTimer.fifth()][i][displayCycle];

    if (patternValue == 1) {
      if (pomodoroTimer.state == 1) {
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
    // returns status if started or aborted
    pomodoroTimer.buttonPressed();
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
