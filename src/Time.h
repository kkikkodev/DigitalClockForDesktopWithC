#ifndef _TIME_H
#define _TIME_H

typedef struct _time{
	int hour;
	int minute;
	int second;
	int amOrPm;
	const char* amOrPmString;
}Time;

Time Time_Create(int hour, int minute, int second, int amOrPm);
Time Time_GetCurrent();
int Time_IsEqual(Time one, Time other);
const int Time_GetHour(Time time);
void Time_SetHour(Time* time, int hour);
const int Time_GetMinute(Time time);
void Time_SetMinute(Time* time, int minute);
const int Time_GetAmOrPm(Time time);
void Time_SetAmOrPm(Time* time, int amOrPm);
const char* Time_GetAmOrPmString(Time time);

#endif