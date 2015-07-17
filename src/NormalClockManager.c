#include <stdio.h>
#include <windows.h>
#include "NormalClockManager.h"
#include "Util.h"
#include "Constant.h"

static void _Date_Print(Date date);
static void _Time_Print(Time time);

void NormalClockManager_Print(NormalClockManager* normalClockManager){
	normalClockManager->currentDate = Date_GetCurrent();
	normalClockManager->currentTime = Time_GetCurrent();
	system("cls");
	FontUtil_ChangeFontColor(LIGHT_JADE);
	_Date_Print(normalClockManager->currentDate);
	FontUtil_ChangeFontColor(LIGHT_GREEN);
	_Time_Print(normalClockManager->currentTime);
	FontUtil_ChangeFontColor(LIGHT_YELLOW);
	CursorUtil_GotoXY(20, 13); // use magic number 
	printf("PRESS ENTER TO MAIN MENU...");
	FontUtil_ChangeFontColor(DEFAULT_FONT_COLOR);
}

static void _Date_Print(Date date){
	CursorUtil_GotoXY(24, 5); // use magic number
	printf("%d. %d. %d (%s)\n", date.year, date.month, date.dayOfMonth, date.dayOfWeekString);
}

static void _Time_Print(Time time){

	//use magic number
	int x = 1;
	int y = 7;
	DigitalPattern_Print(x, y, time.hour / 10, HOUR_LEFT);
	DigitalPattern_Print(x, y, time.hour % 10, HOUR_RIGHT);
	DigitalPattern_Print(x, y, ':', DELIMITER_BETWEEN_HOUR_AND_MINUTE);
	DigitalPattern_Print(x, y, time.minute / 10, MINUTE_LEFT);
	DigitalPattern_Print(x, y, time.minute % 10, MINUTE_RIGHT);
	DigitalPattern_Print(x, y, ':', DELIMITER_BETWEEN_MINUTE_AND_SECOND);
	DigitalPattern_Print(x, y, time.second / 10, SECOND_LEFT);
	DigitalPattern_Print(x, y, time.second % 10, SECOND_RIGHT);
	CursorUtil_GotoXY(x + 64, x + 10);
	printf("%s", time.amOrPmString);
}