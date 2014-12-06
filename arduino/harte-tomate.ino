#include <Bridge.h>
#include <HttpClient.h>
//#include <Process.h>
#include "SimpleTimer.h"
#include "PomodoroTimer.h"
#include "Button.h"
#include "PomodoroTimerEvents.h"
#include "PomodoroTimerStates.h"
#include "LEDRenderer.h"
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

PomodoroTimer pomodoroTimer;
SimpleTimer timer;
Button button(3);
LEDRenderer renderer;
String id;
HttpClient client;
//Process process;

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
  playSound();
}

void loop() {
  timer.run();

  if (button.pressed()) {
    Serial.println("pressed");
    playSound();
    handleEvent(pomodoroTimer.buttonPressed());
  }
}

void handleEvent(PomodoroTimerEvent event) {
  switch (event) {
    case WORK_PERIOD_STARTED:
      Serial.println("Work started. (Make API request)");
//      reportStartOfPomodoro();
      playSound();
      break;
    case PERIOD_ABORTED:
      Serial.println("Period aborted. (Make API request)");
//      reportAbortOfPomodoro();
      Serial.println("done");
      break;
    case REST_PERIOD_STARTED:
      Serial.println("Rest period started. (Play sound)");
      playSound();
//      process.runShellCommand("madplay /mnt/sda1/ring.mp3");
//      while(process.running());
      renderer.reset();
      break;
    case REST_PERIOD_ENDED:
      Serial.println("Rest period ended. (Play sound and make API request)");
//      reportEndOfPomodoro();
      playSound();
//      process.runShellCommand("madplay /mnt/sda1/ring.mp3");
//      while(process.running());
      renderer.reset();
      break;
  }
}

void reportStartOfPomodoro() {
  client.post("http://stravid.com/harte-tomate/pomodori", "token2=h1RYmXbH56GsWKPB");

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
  client.post(url.c_str(), "token2=h1RYmXbH56GsWKPB&event=ended");
  
  while (client.available()) {
    client.read(); 
  }
}

void reportAbortOfPomodoro() {
  String url = "http://stravid.com/harte-tomate/pomodori/" + id;
  client.post(url.c_str(), "token2=h1RYmXbH56GsWKPB&event=aborted");
  
  while (client.available()) {
    client.read(); 
  }
}

void playSound() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    Serial.println("lol");
    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(2, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(2);
  }
}
