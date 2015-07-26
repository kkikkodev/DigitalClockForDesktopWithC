#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>
#include "DigitalClockView.h"
#include "Util.h"
#include "Constant.h"

#pragma comment(lib, "winmm.lib")

#define NORMAL_MUSIC_FILE_NAME ".\\..\\res\\normal_clock.wav"

void DigitalClockView_Init(DigitalClockView* digitalClockView){
	char items[MENU_ITEMS_COUNT][MENU_ITEMS_CONTENT_SIZE] = {
		"[1] Normal Clock", "[2] Alarm Clock", "[3] Exit"
	};
	int menuCount = 3;
	WindowUtil_ChangeWindowSize(WINDOW_LINE_SIZE, WINDOW_COL_SIZE);
	FontUtil_ChangeFontColor(DEFAULT_FONT_COLOR);
	AlarmClockManager_Init(&digitalClockView->alarmClcokManager);
	Menu_Create(&digitalClockView->mainMenu, items, menuCount, 27, 11, DEFAULT_FONT_COLOR); // use magic number
	digitalClockView->selectedMainMenu = -1;
}

void DigitalClockView_ProcessMainMenu(DigitalClockView* digitalClockView){

	// use magic number
	int x = 23;
	int y = 5;
	system("cls");
	CursorUtil_GotoXY(x, y++);
	printf("D I G I T A L");
	x += 2;
	y += 2;
	CursorUtil_GotoXY(x, y++);
	printf("C L O C K");
	x = 37;
	y = 4;
	CursorUtil_GotoXY(x, y++);
	printf("旨收收收收收旬");
	CursorUtil_GotoXY(x, y++);
	printf("早    早    早");
	CursorUtil_GotoXY(x, y++);
	printf("早    早    早");
	CursorUtil_GotoXY(x, y++);
	printf("早  收﹥    早");
	CursorUtil_GotoXY(x, y++);
	printf("早          早");
	CursorUtil_GotoXY(x, y++);
	printf("曲收收收收收旭");
	Menu_Print(digitalClockView->mainMenu);
	digitalClockView->selectedMainMenu = Menu_ProcessKey(&digitalClockView->mainMenu) + 1;
}

void DigitalClockView_ShowNormalClock(DigitalClockView* digitalClockView){
	PlaySound(TEXT(NORMAL_MUSIC_FILE_NAME), NULL, SND_ASYNC | SND_LOOP);
	while (True){
		if (_kbhit() && _getch() == ENTER_KEY_CODE){
			break;
		}
		if (DigitalClockView_IsRinging(*digitalClockView)){
			getchar();
			DigitalClockView_StopAlarm(digitalClockView);
		}
		else{
			PlaySound(TEXT(NORMAL_MUSIC_FILE_NAME), NULL, SND_ASYNC | SND_LOOP);
			NormalClockManager_Print(&digitalClockView->normalClockManager);
		}
		Sleep(MILLI_SECONDS_PER_SECOND - 20);
	}
	PlaySound(NULL, 0, 0);
}

void DigitalClockView_ShowAlarmClock(DigitalClockView* digitalClockView){
	AlarmClockManager_Print(&digitalClockView->alarmClcokManager);
}

const int DigitalClockView_IsRinging(DigitalClockView digitalClockView){
	return AlarmClockManager_IsRinging(digitalClockView.alarmClcokManager);
}

void DigitalClockView_StopAlarm(DigitalClockView* digitalClockView){
	AlarmClockManager_StopAlarm(&digitalClockView->alarmClcokManager);
}
