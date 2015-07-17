#ifndef _DIGITAL_CLOCK_H
#define _DIGITAL_CLOCK_H

#include "NormalClockManager.h"
#include "AlarmClockManager.h"
#include "Menu.h"

typedef struct _digitalClockView{
	NormalClockManager normalClockManager;
	AlarmClockManager alarmClcokManager;
	Menu mainMenu;
	int selectedMainMenu;
}DigitalClockView;

void DigitalClockView_Init(DigitalClockView* digitalClockView);
void DigitalClockView_ProcessMainMenu(DigitalClockView* digitalClockView);
void DigitalClockView_ShowNormalClock(DigitalClockView* digitalClockView);
void DigitalClockView_ShowAlarmClock(DigitalClockView* digitalClockView);
const int DigitalClockView_IsRinging(DigitalClockView digitalClockView);
void DigitalClockView_StopAlarm(DigitalClockView* digitalClockView);

#endif