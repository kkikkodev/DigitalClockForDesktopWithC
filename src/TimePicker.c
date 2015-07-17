#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "TimePicker.h"
#include "Util.h"
#include "Constant.h"

#define EDIT_TYPE_COUNT 4

const static char* onOrOffToPrint[] = { "OFF", "ON" };

static void _TimePicker_ProcessLeftKey(TimePicker* timePicker);
static void _TimePicker_ProcessRightKey(TimePicker* timePicker);
static void _TimePicker_ProcessUpKey(TimePicker* timePicker);
static void _TimePicker_ProcessDownKey(TimePicker* timePicker);

void TimePicker_Init(TimePicker* timePicker){
	memset(timePicker, -1, sizeof(TimePicker));
	timePicker->isActivated = True;
}

void TimePicker_Create(TimePicker* timePicker, int startPositionXToPrint, int startPositionYToPrint){
	timePicker->time = Time_GetCurrent();
	timePicker->onOrOff = OFF_TYPE;
	timePicker->editType = HOUR_EDIT_TYPE;
	timePicker->startPositionToPrint = Point_Create(startPositionXToPrint, startPositionYToPrint);
	timePicker->isActivated = True;
}

int TimePicker_IsFirst(TimePicker timePicker){
	return Time_GetHour(timePicker.time) == -1; // because -1 is the initial value
}

void TimePicker_Print(TimePicker timePicker){
	CursorUtil_Hide();
	Point startPositionToPrint = timePicker.startPositionToPrint;
	system("cls");
	FontUtil_ChangeFontColor(WHITE);
	if (timePicker.editType == HOUR_EDIT_TYPE){
		FontUtil_ChangeFontColor(LIGHT_YELLOW);
	}
	DigitalPattern_Print(startPositionToPrint.x, startPositionToPrint.y, Time_GetHour(timePicker.time) / 10, HOUR_LEFT);
	DigitalPattern_Print(startPositionToPrint.x, startPositionToPrint.y, Time_GetHour(timePicker.time) % 10, HOUR_RIGHT);
	FontUtil_ChangeFontColor(WHITE);
	DigitalPattern_Print(startPositionToPrint.x, startPositionToPrint.y, ':', DELIMITER_BETWEEN_HOUR_AND_MINUTE);
	if (timePicker.editType == MINUTE_EDIT_TYPE){
		FontUtil_ChangeFontColor(LIGHT_YELLOW);
	}
	DigitalPattern_Print(startPositionToPrint.x, startPositionToPrint.y, Time_GetMinute(timePicker.time) / 10, MINUTE_LEFT);
	DigitalPattern_Print(startPositionToPrint.x, startPositionToPrint.y, Time_GetMinute(timePicker.time) % 10, MINUTE_RIGHT);
	FontUtil_ChangeFontColor(WHITE);
	if (timePicker.editType == AM_OR_PM_EDIT_TYPE){
		FontUtil_ChangeFontColor(LIGHT_YELLOW);
	}
	CursorUtil_GotoXY(startPositionToPrint.x + 42, startPositionToPrint.y + 4);
	printf("%s", Time_GetAmOrPmString(timePicker.time));
	FontUtil_ChangeFontColor(WHITE);
	if (timePicker.editType == ON_OR_OFF_EDIT_TYPE){
		FontUtil_ChangeFontColor(LIGHT_YELLOW);
	}
	CursorUtil_GotoXY(startPositionToPrint.x + 20, startPositionToPrint.y + 6);
	printf("%s", onOrOffToPrint[timePicker.onOrOff]);
	FontUtil_ChangeFontColor(WHITE);
	CursorUtil_GotoXY(startPositionToPrint.x + 7, startPositionToPrint.y + 8);
	printf("PRESS ENTER TO MAIN MENU...");
	FontUtil_ChangeFontColor(DEFAULT_FONT_COLOR);
}

void TimePicker_ProcessKey(TimePicker* timePicker){
	while (True){

		// if time picker is activated, process time picker key input
		if (timePicker->isActivated){
			if (_kbhit()){
				int key = _getch();
				if (key == ENTER_KEY_CODE){
					break;
				}
				switch (key){
				case 0xE0:
					if (_kbhit()){
						key = _getch();
						if (key == LEFT_KEY_CODE){
							_TimePicker_ProcessLeftKey(timePicker);
						}
						else if (key == RIGHT_KEY_CODE){
							_TimePicker_ProcessRightKey(timePicker);
						}
						else if (key == UP_KEY_CODE){
							_TimePicker_ProcessUpKey(timePicker);
						}
						else if (key == DOWN_KEY_CODE){
							_TimePicker_ProcessDownKey(timePicker);
						}
						TimePicker_Print(*timePicker);
					}
					break;
				}
			}
		}

		// otherwise, process other module key input
		else{
			int key = _getch();
			if (key == ENTER_KEY_CODE){
				break; // terminate processing key function
			}
		}
	}
}

const int TimePicker_GetHour(TimePicker timePicker){
	return Time_GetHour(timePicker.time);
}

const int TimePicker_GetMinute(TimePicker timePicker){
	return Time_GetMinute(timePicker.time);
}

const int TimePicker_GetAmOrPm(TimePicker timePicker){
	return Time_GetAmOrPm(timePicker.time);
}

void TimePicker_SetEditType(TimePicker* timePicker, int editType){
	timePicker->editType = editType;
}

void TimePicker_SetOnOrOff(TimePicker* timePicker, int onOrOff){
	timePicker->onOrOff = onOrOff;
}

const int TimePicker_GetOnOrOff(TimePicker timePicker){
	return timePicker.onOrOff;
}

void TimePicker_SetIsActivated(TimePicker* timePicker, int isActivated){
	timePicker->isActivated = isActivated;
}

const int TimePicker_GetIsActivated(TimePicker timePicker){
	return timePicker.isActivated;
}

static void _TimePicker_ProcessLeftKey(TimePicker* timePicker){
	timePicker->editType = (timePicker->editType - 1 + EDIT_TYPE_COUNT) % EDIT_TYPE_COUNT;
}

static void _TimePicker_ProcessRightKey(TimePicker* timePicker){
	timePicker->editType = (timePicker->editType + 1) % EDIT_TYPE_COUNT;
}

static void _TimePicker_ProcessUpKey(TimePicker* timePicker){
	if (timePicker->editType == HOUR_EDIT_TYPE){
		Time_SetHour(&timePicker->time, (Time_GetHour(timePicker->time) + 1) % (12 + 1));
		if (Time_GetHour(timePicker->time) == 0){
			Time_SetHour(&timePicker->time, 1);
		}
	}
	else if (timePicker->editType == MINUTE_EDIT_TYPE){
		Time_SetMinute(&timePicker->time, (Time_GetMinute(timePicker->time) + 1) % 60);
	}
	else if (timePicker->editType == AM_OR_PM_EDIT_TYPE){
		int amOrPm = 1 - Time_GetAmOrPm(timePicker->time);
		Time_SetAmOrPm(&timePicker->time, amOrPm);
	}
	else if (timePicker->editType == ON_OR_OFF_EDIT_TYPE){
		timePicker->onOrOff = 1 - timePicker->onOrOff;
	}
}

static void _TimePicker_ProcessDownKey(TimePicker* timePicker){
	if (timePicker->editType == HOUR_EDIT_TYPE){
		Time_SetHour(&timePicker->time, (Time_GetHour(timePicker->time) - 1 + (12 + 1)) % (12 + 1));
		if (Time_GetHour(timePicker->time) == 0){
			Time_SetHour(&timePicker->time, 12);
		}
	}
	else if (timePicker->editType == MINUTE_EDIT_TYPE){
		Time_SetMinute(&timePicker->time, (Time_GetMinute(timePicker->time) - 1) % 60);
	}
	else if (timePicker->editType == AM_OR_PM_EDIT_TYPE){
		int amOrPm = 1 - Time_GetAmOrPm(timePicker->time);
		Time_SetAmOrPm(&timePicker->time, amOrPm);;
	}
	else if (timePicker->editType == ON_OR_OFF_EDIT_TYPE){
		timePicker->onOrOff = 1 - timePicker->onOrOff;
	}
}