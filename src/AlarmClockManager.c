#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <mmsystem.h>
#include "AlarmClockManager.h"
#include "DigitalClockView.h"
#include "Constant.h"
#include "Util.h"

#pragma comment(lib, "winmm.lib")

#define ALARM_MUSIC_FILE_NAME ".\\..\\res\\alarm_clock.wav"

// it is used in AlarmClockManager_RingAlarm and AlarmClockManager_StopAlarm funtions
// it is originated from Main.c file
extern DigitalClockView digitalClockView;

static DWORD WINAPI _AlarmClockManager_OnAlarmThreadStarted(void *alarmClockManager);
static int _AlarmClockManager_ProcessRingingAlarm(AlarmClockManager* alarmClockManager);
static void _AlarmClockManager_RingAlarm(AlarmClockManager* alarmClockManager);
static void _PrintAlarm();

void AlarmClockManager_Init(AlarmClockManager* alarmClockManager){
	TimePicker_Init(&alarmClockManager->timePicker);
	alarmClockManager->isRinging = False;
	alarmClockManager->alarmThread = 0;
}

void AlarmClockManager_Print(AlarmClockManager* alarmClockManager){
	if (TimePicker_IsFirst(alarmClockManager->timePicker)){
		TimePicker_Create(&alarmClockManager->timePicker, 13, 5); // use magic number
	}
	TimePicker_SetEditType(&alarmClockManager->timePicker, HOUR_EDIT_TYPE);
	TimePicker_Print(alarmClockManager->timePicker);
	TimePicker_ProcessKey(&alarmClockManager->timePicker);
	if (TimePicker_GetOnOrOff(alarmClockManager->timePicker)){
		DWORD alarmThreadID;
		alarmClockManager->alarmThread = (HANDLE)_beginthreadex(NULL, 0, _AlarmClockManager_OnAlarmThreadStarted, alarmClockManager, 0, (unsigned *)&alarmThreadID);
	}
}

void AlarmClockManager_StopAlarm(AlarmClockManager* alarmClockManager){
	PlaySound(NULL, 0, 0);
	alarmClockManager->isRinging = False;
	TimePicker_SetOnOrOff(&alarmClockManager->timePicker, OFF_TYPE);
	Menu_SetIsActivated(&digitalClockView.mainMenu, True);
	TimePicker_SetIsActivated(&alarmClockManager->timePicker, True);
}

const int AlarmClockManager_IsRinging(AlarmClockManager alarmClockManager){
	return alarmClockManager.isRinging;
}

static DWORD WINAPI _AlarmClockManager_OnAlarmThreadStarted(void *alarmClockManager){
	while (True){
		Sleep(MILLI_SECONDS_PER_SECOND);
		if (_AlarmClockManager_ProcessRingingAlarm((AlarmClockManager*)alarmClockManager)){
			break;
		}
	}
	return 0;
}

static int _AlarmClockManager_ProcessRingingAlarm(AlarmClockManager* alarmClockManager){
	if (!TimePicker_GetOnOrOff(alarmClockManager->timePicker)){
		return False;
	}
	Time alarmTime = Time_Create(TimePicker_GetHour(alarmClockManager->timePicker),
		TimePicker_GetMinute(alarmClockManager->timePicker),
		0, TimePicker_GetAmOrPm(alarmClockManager->timePicker));
	Time currentTime = Time_GetCurrent();
	if (Time_IsEqual(alarmTime, currentTime)){
		_AlarmClockManager_RingAlarm(alarmClockManager);
		return True; // for blocking duplicate ringing alarm
	}
	else{
		return False;
	}
}

static void _AlarmClockManager_RingAlarm(AlarmClockManager* alarmClockManager){
	PlaySound(TEXT(ALARM_MUSIC_FILE_NAME), NULL, SND_ASYNC | SND_LOOP);
	alarmClockManager->isRinging = True;
	Menu_SetIsActivated(&digitalClockView.mainMenu, False);
	TimePicker_SetIsActivated(&alarmClockManager->timePicker, False);
	_PrintAlarm();
}

static void _PrintAlarm(){

	// use magic number
	int x = 22;
	int y = 1;
	system("cls");
	CursorUtil_GotoXY(x, y++);
	printf("    ﹥          ﹥");
	CursorUtil_GotoXY(x, y++);
	printf("  ﹥﹥﹥      ﹥﹥﹥");
	CursorUtil_GotoXY(x, y++);
	printf(" ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥");
	CursorUtil_GotoXY(x, y++);
	printf("﹥                  ﹥");
	CursorUtil_GotoXY(x, y++);
	printf("﹥        早        ﹥");
	CursorUtil_GotoXY(x, y++);
	printf("﹥        早        ﹥");
	CursorUtil_GotoXY(x, y++);
	printf("﹥        早        ﹥");
	CursorUtil_GotoXY(x, y++);
	printf("﹥    收收﹥        ﹥");
	CursorUtil_GotoXY(x, y++);
	printf("﹥                  ﹥");
	CursorUtil_GotoXY(x, y++);
	printf("﹥                  ﹥");
	CursorUtil_GotoXY(x, y++);
	printf("﹥                  ﹥");
	CursorUtil_GotoXY(x, y++);
	printf(" ﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥");
	CursorUtil_GotoXY(x, y++);
	printf("    ﹥          ﹥");
	CursorUtil_GotoXY(x, y++);
	printf("   ﹥            ﹥");
	CursorUtil_GotoXY(x - 2, y + 1);
	printf("PRESS ENTER TO MAIN MENU...");
}