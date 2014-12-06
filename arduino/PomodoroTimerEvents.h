#ifndef POMODORO_TIMER_EVENTS_H
#define POMODORO_TIMER_EVENTS_H
enum PomodoroTimerEvent {
	NONE,
	WORK_PERIOD_STARTED,
	REST_PERIOD_STARTED,
	PERIOD_ABORTED,
	REST_PERIOD_ENDED
};
#endif