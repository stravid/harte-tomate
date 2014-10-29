#include <Bridge.h>
#include <HttpClient.h>
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
String id;
HttpClient client;

void tick() {
  updatePomodoroTimer();
  updateDisplay();
}

void updatePomodoroTimer() {
  handleEvent(pomodoroTimer.update());
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
    handleEvent(pomodoroTimer.buttonPressed());
  }
}

void handleEvent(PomodoroTimerEvent event) {
  switch (event) {
    case WORK_PERIOD_STARTED:
      Serial.println("Work started. (Make API request)");
      reportStartOfPomodoro();
      break;
    case PERIOD_ABORTED:
      Serial.println("Period aborted. (Make API request)");
      reportAbortOfPomodoro();
      break;
    case REST_PERIOD_STARTED:
      Serial.println("Rest period started. (Play sound)");
      renderer.reset();
      break;
    case REST_PERIOD_ENDED:
      Serial.println("Rest period ended. (Play sound and make API request)");
      reportEndOfPomodoro();
      renderer.reset();
      break;
  }
}

void reportStartOfPomodoro() {
  String response = "";
  int start, end;
  
  client.post("http://192.168.0.11:4567", "");

  while (client.available()) {
    char character = client.read();
    response += character;
  }

  start = response.indexOf("id");
  end = response.indexOf("}", start);
  id = response.substring(start + 4, end);
}

void reportEndOfPomodoro() {
  String url = "http://192.168.0.11:4567/" + id;
  client.post(url.c_str(), "{\"event\":\"ended\"}");
}

void reportAbortOfPomodoro() {
  String url = "http://192.168.0.11:4567/" + id;
  client.post(url.c_str(), "{\"event\":\"aborted\"}");
}
