#ifndef LED_RENDERER_H
#define LED_RENDERER_H

#include "led.h"
#include "PomodoroTimer.h"

class LEDRenderer {
  public:
    void update(PomodoroTimer pt);
    void reset();
    // bool pressed();

  private:
    LED leds[5] = { LED(12, 11), LED(10, 9), LED(8, 7), LED(6, 5), LED(4, 3) };
    int workPattern[5][5][4] = {
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
    
    int restPattern[5][5][4];
    int displayCycle;
    void displayPattern(int pattern[]);
};
#endif
