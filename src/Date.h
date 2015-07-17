#ifndef _DATE_H
#define _DATE_H

typedef struct _date{
	int year;
	int month;
	int dayOfMonth;
	int dayOfWeek;
	const char* dayOfWeekString;
}Date;

Date Date_Create(int year, int month, int dayOfMonth, int dayOfWeek);
Date Date_GetCurrent();
int Date_IsEqual(Date one, Date other);

#endif