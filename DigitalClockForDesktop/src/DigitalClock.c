#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "DigitalClock.h"
#include "Util.h"

#define GMT (+9)

#define DAY_OF_WEEK_SIZE 7

const static char* DAY_OF_WEEK[DAY_OF_WEEK_SIZE] = {
	" Sun ", " Mon ", " Tue ", " Wed ", " Thu ", " Fri ", " Sat "
};

#define PATTERNS_TO_PRINT_LENGTH 11
#define PATTERNS_TO_PRINT_ROW 5
#define PATTERNS_TO_PRINT_COL 3

const static char patternsToPrint[PATTERNS_TO_PRINT_LENGTH][PATTERNS_TO_PRINT_ROW][PATTERNS_TO_PRINT_COL] = {
	{ // 0
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 0, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 }
	},
	{ // 1
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 },
		{ 0, 1, 0 }
	},
	{ // 2
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 },
		{ 1, 0, 0 },
		{ 1, 1, 1 }
	},
	{ // 3
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 }
	},
	{ // 4
		{ 1, 0, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 }
	},
	{ // 5
		{ 1, 1, 1 },
		{ 1, 0, 0 },
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 }
	},
	{ // 6
		{ 1, 0, 0 },
		{ 1, 0, 0 },
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 }
	},
	{ // 7
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 0, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 }
	},
	{ // 8
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 }
	},
	{ // 9
		{ 1, 1, 1 },
		{ 1, 0, 1 },
		{ 1, 1, 1 },
		{ 0, 0, 1 },
		{ 0, 0, 1 }
	},
	{ // :
		{ 0, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 0 }
	}
};

static void _DigitalClock_PrintDate(DigitalClock digitalClock);
static void _DigitalClock_PrintTime(DigitalClock digitalClock);

static void _PrintPattern(int pattern, int type);

DigitalClock DigitalClock_GetTime(){
	DigitalClock digitalClock = {0, };
	time_t now = time(NULL);
	struct tm* time = gmtime(&now);
	digitalClock.year = time->tm_year + 1900;
	digitalClock.month = time->tm_mon + 1;
	digitalClock.dayOfMonth = time->tm_mday;
	digitalClock.dayOfWeek = time->tm_wday;
	digitalClock.hour = (time->tm_hour + GMT) % 24;
	digitalClock.minute = time->tm_min;
	digitalClock.second = time->tm_sec;
	return digitalClock;
}

void DigitalClock_Print(DigitalClock digitalClock){
	_DigitalClock_PrintDate(digitalClock);
	_DigitalClock_PrintTime(digitalClock);
	Sleep(ONE_SECOND - 20);
}

static void _DigitalClock_PrintDate(DigitalClock digitalClock){
	CursorUtil_GotoXY(INITIAL_X_POSITION_FOR_DATE, INITIAL_Y_POSITION_FOR_DATE);
	printf("%d. %d. %d (%s)\n", digitalClock.year, digitalClock.month,
		digitalClock.dayOfMonth, DAY_OF_WEEK[digitalClock.dayOfWeek]);
}

static void _DigitalClock_PrintTime(DigitalClock digitalClock){
	_PrintPattern(digitalClock.hour / 10, HOUR_LEFT);
	_PrintPattern(digitalClock.hour % 10, HOUR_RIGHT);
	_PrintPattern(':', DELIMITER_BETWEEN_HOUR_AND_MINUTE);
	_PrintPattern(digitalClock.minute / 10, MINUTE_LEFT);
	_PrintPattern(digitalClock.minute % 10, MINUTE_RIGHT);
	_PrintPattern(':', DELIMITER_BETWEEN_MINUTE_AND_SECOND);
	_PrintPattern(digitalClock.second / 10, SECOND_LEFT);
	_PrintPattern(digitalClock.second % 10, SECOND_RIGHT);
}

static void _PrintPattern(int pattern, int type){
	int i = 0;
	int j = 0;
	int x = INITIAL_X_POSITION_FOR_TIME;
	int y = INITIAL_Y_POSITION_FOR_TIME;
	for (i = 0; i < type; i++){
		x += Y_OFFSET_FOR_TIME;
	}
	if (!(pattern >= 0 && pattern <= 9)){
		pattern = PATTERNS_TO_PRINT_LENGTH - 1;
	}
	CursorUtil_GotoXY(x, y++);
	for (i = 0; i < PATTERNS_TO_PRINT_ROW; i++){
		for (j = 0; j < PATTERNS_TO_PRINT_COL; j++){
			if (patternsToPrint[pattern][i][j]){
				printf("бс");
			}
			else{
				printf("  ");
			}
		}
		CursorUtil_GotoXY(x, y++);
	}
}