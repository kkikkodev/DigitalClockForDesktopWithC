#include <time.h>
#include "Date.h"

const static char* DAY_OF_WEEK_STRINGS[] = {
	"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};

Date Date_Create(int year, int month, int dayOfMonth, int dayOfWeek){
	Date date = { year, month, dayOfMonth, dayOfWeek, DAY_OF_WEEK_STRINGS[date.dayOfWeek] };
	return date;
}

Date Date_GetCurrent(){
	Date currentDate;
	time_t now = time(NULL);
	struct tm* time = gmtime(&now);
	currentDate.year = time->tm_year + 1900;
	currentDate.month = time->tm_mon + 1;
	currentDate.dayOfMonth = time->tm_mday;
	currentDate.dayOfWeek = time->tm_wday;
	currentDate.dayOfWeekString = DAY_OF_WEEK_STRINGS[currentDate.dayOfWeek];
	return currentDate;
}

int Date_IsEqual(Date one, Date other){
	return one.year == other.year && one.month == other.month && one.dayOfMonth == other.dayOfMonth;
}