#include <time.h>
#include "Time.h"

#define GMT (+9)

enum AmOrPmType{
	NONE = -1, AM_TYPE, PM_TYPE
};

const static char* AM_OR_PM_STRINGS[] = { "AM", "PM" };

Time Time_Create(int hour, int minute, int second, int amOrPm){
	Time time;
	if (amOrPm == NONE){
		time.hour = hour % 12;
		time.amOrPm = hour / 12;
	}
	else{
		time.hour = hour;
		time.amOrPm = amOrPm;
	}
	time.amOrPmString = AM_OR_PM_STRINGS[time.amOrPm];
	time.minute = minute;
	time.second = second;
	return time;
}

Time Time_GetCurrent(){
	Time currentTime;
	time_t now = time(NULL);
	struct tm* time = gmtime(&now);
	currentTime.hour = (time->tm_hour + GMT) % 12;
	if (currentTime.hour == 0){
		currentTime.hour = 12;
	}
	currentTime.minute = time->tm_min;
	currentTime.second = time->tm_sec;
	currentTime.amOrPm = (time->tm_hour + GMT) % 24 / 12;
	currentTime.amOrPmString = AM_OR_PM_STRINGS[currentTime.amOrPm];
	return currentTime;
}

int Time_IsEqual(Time one, Time other){
	return one.hour == other.hour && one.minute == other.minute && one.second == other.second && one.amOrPm == other.amOrPm;
}

const int Time_GetHour(Time time){
	return time.hour;
}

void Time_SetHour(Time* time, int hour){
	time->hour = hour;
}

const int Time_GetMinute(Time time){
	return time.minute;
}

void Time_SetMinute(Time* time, int minute){
	time->minute = minute;
}

const int Time_GetAmOrPm(Time time){
	return time.amOrPm;
}

void Time_SetAmOrPm(Time* time, int amOrPm){
	time->amOrPm = amOrPm;
	time->amOrPmString = AM_OR_PM_STRINGS[time->amOrPm]; 
}

const char* Time_GetAmOrPmString(Time time){
	return time.amOrPmString;
}