#ifndef _ALARM_CLOCK_MANAGER_H
#define _ALARM_CLOCK_MANAGER_H

#include <windows.h>
#include "TimePicker.h"

typedef struct _alarmClockManager{
	TimePicker timePicker;
	int isRinging;
	HANDLE alarmThread;
}AlarmClockManager;

void AlarmClockManager_Init(AlarmClockManager* alarmClockManager);
void AlarmClockManager_Print(AlarmClockManager* alarmClockManager);
void AlarmClockManager_StopAlarm(AlarmClockManager* alarmClockManager);
const int AlarmClockManager_IsRinging(AlarmClockManager alarmClockManager);

#endif