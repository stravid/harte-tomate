#include <Bridge.h>
#include <HttpClient.h>
#include "SimpleTimer.h"
#include "PomodoroTimer.h"
#include "Button.h"
#include "PomodoroTimerEvents.h"
#include "PomodoroTimerStates.h"
#include "LEDRenderer.h"
#include "SoundManager.h"
#include "Environment.h"

PomodoroTimer pomodoroTimer;
SimpleTimer timer;
Button button(3);
LEDRenderer renderer;
String id;
HttpClient client;
SoundManager soundManager(2);

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
      reportStartOfPomodoro();
      break;
    case WORK_PERIOD_ENDED:
      reportEndOfPomodoro();
      soundManager.playWorkPeriodStopped();
      renderer.reset();
      break;
    case WORK_PERIOD_ABORTED:
      reportAbortOfPomodoro();
      renderer.reset();
      break;
    case REST_PERIOD_ENDED:
      soundManager.playRestPeriodStopped();
      renderer.reset();
      break;
    case REST_PERIOD_ABORTED:
      renderer.reset();
      break;
  }
}

void reportStartOfPomodoro() {
  client.post("http://stravid.com/harte-tomate/pomodori", (char*)String("token2=").concat(TOKEN));

  String response = "";
  int start, end;

  while (client.available()) {
    char character = client.read();
    response += character;
  }

  start = response.indexOf("id");
  end = response.indexOf("\"}", start);
  id = response.substring(start + 5, end);
}

void reportEndOfPomodoro() {
  String url = "http://stravid.com/harte-tomate/pomodori/" + id;
//  client.post(url.c_str(), "token2=h1RYmXbH56GsWKPB&event=ended");
  client.post(url.c_str(), (char*)String(String("token2=").concat(TOKEN)).concat("&event=ended"));

  while (client.available()) {
    client.read();
  }
}

void reportAbortOfPomodoro() {
  String url = "http://stravid.com/harte-tomate/pomodori/" + id;
//  client.post(url.c_str(), "token2=h1RYmXbH56GsWKPB&event=aborted");
  client.post(url.c_str(), (char*)String(String("token2=").concat(TOKEN)).concat("&event=aborted"));

  while (client.available()) {
    client.read();
  }
}
