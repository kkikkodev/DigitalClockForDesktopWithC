#ifndef _TIME_PICKER_H
#define _TIME_PICKER_H

#include "Point.h"
#include "Time.h"

enum AmOrPmType{
	AM_TYPE, PM_TYPE
};

enum OnOrOffType{
	OFF_TYPE, ON_TYPE
};

enum EditType{
	HOUR_EDIT_TYPE, MINUTE_EDIT_TYPE, AM_OR_PM_EDIT_TYPE, ON_OR_OFF_EDIT_TYPE
};

typedef struct _timePicker{
	Time time;
	int editType;
	int onOrOff;
	Point startPositionToPrint;
	int isActivated; // if this is true, key input of time picker is processed, otherwise, not key input of time picker but key input of other module is processed
}TimePicker;

void TimePicker_Init(TimePicker* timePicker);
void TimePicker_Create(TimePicker* timePicker, int startPositionXToPrint, int startPositionYToPrint);
int TimePicker_IsFirst(TimePicker timePicker);
void TimePicker_Print(TimePicker timePicker);
void TimePicker_ProcessKey(TimePicker* timePicker);
const int TimePicker_GetHour(TimePicker timePicker);
const int TimePicker_GetMinute(TimePicker timePicker);
const int TimePicker_GetAmOrPm(TimePicker timePicker);
void TimePicker_SetEditType(TimePicker* timePicker, int editType);
void TimePicker_SetOnOrOff(TimePicker* timePicker, int onOrOff);
const int TimePicker_GetOnOrOff(TimePicker timePicker);
void TimePicker_SetIsActivated(TimePicker* timePicker, int isActivated);
const int TimePicker_GetIsActivated(TimePicker timePicker);

#endif