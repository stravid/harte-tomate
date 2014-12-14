#ifndef LED_RENDERER_H
#define LED_RENDERER_H

#include "led.h"
#include "PomodoroTimer.h"

class LEDRenderer {
  public:
    void update(PomodoroTimer pt);
    void reset();

  private:
    LED leds[5] = { LED(13, 12), LED(11, 10), LED(9, 8), LED(7, 6), LED(5, 4) };

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

    int restPattern[5][5][4] = {
      {
        { 2, 2, 2, 2 },
        { 2, 2, 2, 2 },
        { 2, 2, 2, 2 },
        { 2, 2, 2, 2 },
        { 2, 0, 2, 0 }
      },
      {
        { 2, 2, 2, 2 },
        { 2, 2, 2, 2 },
        { 2, 2, 2, 2 },
        { 2, 0, 2, 0 },
        { 0, 0, 0, 0 }
      },
      {
        { 2, 2, 2, 2 },
        { 2, 2, 2, 2 },
        { 2, 0, 2, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
      },
      {
        { 2, 2, 2, 2 },
        { 2, 0, 2, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
      },
      {
        { 2, 0, 2, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
      }
    };

    int displayCycle;
    void displayPattern(int pattern[]);
};
#endif
