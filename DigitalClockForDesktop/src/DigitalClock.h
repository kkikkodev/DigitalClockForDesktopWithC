#ifndef _DIGITAL_CLOCK_H
#define _DIGITAL_CLOCK_H

// ex) 12:24:36
enum{
	HOUR_LEFT, // left digit of hour  
	HOUR_RIGHT, // right digit of hour
	DELIMITER_BETWEEN_HOUR_AND_MINUTE, // colon between hour and minute 
	MINUTE_LEFT, // left digit of minute
	MINUTE_RIGHT, // right digit of minute
	DELIMITER_BETWEEN_MINUTE_AND_SECOND, // colon between minute and second
	SECOND_LEFT, // left digit of second
	SECOND_RIGHT // right digit of second
};

typedef struct _digitalClock{
	int year;
	int month;
	int dayOfMonth;
	int dayOfWeek; // Sunday (0), Monday (1), ...
	int hour;
	int minute;
	int second;
}DigitalClock;

#define ONE_SECOND 1000
#define INITIAL_X_POSITION_FOR_TIME 2
#define INITIAL_Y_POSITION_FOR_TIME 3
#define Y_OFFSET_FOR_TIME 8
#define INITIAL_X_POSITION_FOR_DATE 22
#define INITIAL_Y_POSITION_FOR_DATE 1

#define TRUE 1
#define FALSE 0

DigitalClock DigitalClock_GetTime();
void DigitalClock_Print(DigitalClock digitalClock);

#endif